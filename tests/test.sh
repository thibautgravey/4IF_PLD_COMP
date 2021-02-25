cd ..
docker run --rm -v $(pwd):/work eguerin/antlr4cpp bash -c "cd /work/tests ; chmod 755 pld-wrapper.sh; python3 pld-test.py tests/Init/"
