#!/usr/bin/env python3

import argparse
import glob
import os
import shutil
import sys
import subprocess

def command(string, logfile=None):
    """execute `string` as a shell command, optionnaly logging stdout+stderr to a file. return exit status.)"""
    if args.verbose:
        print("pld-test.py: "+string)
    try:
        output=subprocess.check_output(string,stderr=subprocess.STDOUT,shell=True)
        ret= 0
    except subprocess.CalledProcessError as e:
        ret=e.returncode
        output = e.output

    if logfile:
        f=open(logfile,'w')
        print(output.decode(sys.stdout.encoding)+'\n'+'return code: '+str(ret),file=f)
        f.close()

    return ret

def dumpfile(name):
    print(open(name).read(),end='')

######################################################################################
## ARGPARSE step: make sense of our command-line arguments

argparser   = argparse.ArgumentParser(
description = "Compile each test-case  with both GCC and PLD, and then compare the results.",
epilog      = ""
)

argparser.add_argument('input',metavar='PATH',nargs='+',help='For each argument:'
                       +' if it points to a file, use this file as a test-case;'
                       +' if it points to a directory, use all *.c files in subtree as test-cases.')

argparser.add_argument('-d','--debug',action="count",default=0,
                       help='Increase quantity of debugging messages (only useful to debug the test script itself)')
argparser.add_argument('-v','--verbose',action="count",default=0,
                       help='Increase verbosity level. You can use this option multiple times.')
argparser.add_argument('-w','--wrapper',metavar='PATH',
                       help='Invoke the PLD compiler through the shell script at PATH. (default: use `pld-wrapper.sh` from the same directory as pld-test.py)')




args=argparser.parse_args()

if args.debug >=2:
    print('debug: command-line arguments '+str(args))

orig_cwd=os.getcwd()
if "pld-test-output" in orig_cwd:
    ## we are invoked from within a preexisting DEST subtree => let's use it in place
    DEST="./"
    while os.path.basename(os.path.realpath('.')) != 'pld-test-output':
        os.chdir('..')
        DEST="../"+DEST
    os.chdir(orig_cwd)
    DEST=os.path.normpath(DEST)
    if args.debug:
        print('debug: DEST tree is at `'+DEST+"'")
else:
    ## create a new DEST subtree if required
    if not os.path.isdir('pld-test-output'):
        os.mkdir('pld-test-output')
    DEST='pld-test-output'
    
## Then we process the inputs arguments i.e. filenames or subtrees
inputfilenames=[]
for path in args.input:
    path=os.path.normpath(path) # collapse redundant slashes etc.
    if os.path.isfile(path):
        if path[-2:] == '.c':
            inputfilenames.append(path)
        else:
            print("error: incorrect filename suffix (should be '.c'): "+path)
    elif os.path.isdir(path):
        for dirpath,dirnames,filenames in os.walk(path):
            # if os.path.samefile(dirpath,args.outdir):
            #     print("error: INPUT directory:`"+path+"' contains OUTDIR `"+args.outdir+"'")
            #     sys.exit(1)
            inputfilenames+=[dirpath+'/'+name for name in filenames if name[-2:]=='.c']
    else:
        print("error: cannot read input path `"+path+"'")
        sys.exit(1)

## debug: after treewalk
if args.debug:
    print("debug: list of files after tree walk:"," ".join(inputfilenames))

## sanity check
if len(inputfilenames) == 0:
    print("error: found no test-case in: "+" ".join(args.input))
    sys.exit(1)

## Here we check that  we can actually read the files.  Our goal is to
## fail as early as possible when the CLI arguments are wrong.
for inputfilename in inputfilenames:
    try:
        f=open(inputfilename,"r")
        f.close()
    except Exception as e:
        print("error: "+e.args[1]+": "+inputfilename)
        sys.exit(1)

## Last but not least: we now locate the "wrapper script" that we will
## use to invoke the padawan compiler

if args.wrapper:
    wrapper=os.path.realpath(os.getcwd()+"/"+ args.wrapper)
else:
    wrapper=os.path.dirname(os.path.realpath(__file__))+"/pld-wrapper.sh"

if not os.path.isfile(wrapper):
    print("error: cannot find "+os.path.basename(wrapper)+" in directory: "+os.path.dirname(wrapper))
    exit(1)

if args.debug:
    print("debug: wrapper path: "+wrapper)
        
######################################################################################
## PREPARE step: copy all test-cases under DEST

jobs=[]

for inputfilename in inputfilenames:
    if args.debug>=2:
        print("debug: PREPARING "+inputfilename)

    if ('pld-test-output' in os.path.realpath(inputfilename)
        and inputfilename[-7:] == 'input.c' ) :
        # print("ALREADY PREPARED")
        jobs.append(os.path.dirname(inputfilename))
    else:
        ## each test-case gets copied and processed in its own subdirectory:
        ## ../somedir/subdir/file.c becomes ./pld-test-output/somedir-subdir-file/input.c
        subdir=DEST+'/'+inputfilename.strip("./")[:-2].replace('/','-')
        if not os.path.isdir(subdir):
            os.mkdir(subdir)
            shutil.copyfile(inputfilename, subdir+'/input.c')
        jobs.append(subdir)

## eliminate duplicate paths from the 'jobs' list
unique_jobs=[]
for j in jobs:
    for d in unique_jobs:
        if os.path.samefile(j,d):
            break # and skip the 'else' branch
    else:
        unique_jobs.append(j)
jobs=unique_jobs
# debug: after deduplication
if args.debug:
    print("debug: list of test-cases after deduplication:"," ".join(jobs))


######################################################################################
## TEST step: actually compile all test-cases with both compilers

for jobname in jobs:
    os.chdir(orig_cwd)

    print('TEST-CASE: '+jobname)
    os.chdir(jobname)
    
    ## JEDI compiler, aka GCC
    gccstatus=command("gcc -S -o asm-gcc.s input.c", "gcc-compile.txt")
    if gccstatus == 0:
        # test-case is a valid program. we should run it
        ldstatus=command("gcc -o exe-gcc asm-gcc.s", "gcc-link.txt")
        if ldstatus:
            print("unexpected error: linker failed to produce exe-gcc !")
            continue
        exegccstatus=command("./exe-gcc", "gcc-execute.txt")
        if args.verbose >=2:
            dumpfile("gcc-execute.txt")
            
    ## PADAWAN compiler
    pldstatus=command(wrapper+" asm-pld.s input.c", "pld-compile.txt")
    
    if gccstatus != 0 and pldstatus != 0:
        ## padawan correctly rejects invalid program -> test-case ok
        print("TEST OK")
        continue
    elif gccstatus != 0 and pldstatus == 0:
        ## padawan wrongly accepts invalid program -> error
        print("TEST FAIL (your compiler accepts an invalid program)")
        continue
    elif gccstatus == 0 and pldstatus != 0:
        ## padawan wrongly rejects valid program -> error
        print("TEST FAIL (your compiler rejects a valid program)")
        if args.verbose:
            dumpfile("pld-compile.txt")
        continue
    else:
        ## padawan accepts to compile valid program -> let's link it
        ldstatus=command("gcc -o exe-pld asm-pld.s", "pld-link.txt")
        if ldstatus:
            print("TEST FAIL (your compiler produces incorrect assembly)")
            if args.verbose:
                dumpfile("pld-link.txt")
            continue

    ## both compilers  did produce an  executable, so now we  run both
    ## these executables and compare the results.
        
    exepldstatus=command("./exe-pld","pld-execute.txt")
    if open("gcc-execute.txt").read() != open("pld-execute.txt").read() :
        print("TEST FAIL (different results at execution)")
        if args.verbose:
            print("GCC:")
            dumpfile("gcc-execute.txt")
            print("you:")
            dumpfile("pld-execute.txt")
        continue

    ## last but not least
    print("TEST OK")
