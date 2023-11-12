#!/bin/bash

#    --regex-range="<listing lang="cpp"><!\[CDATA\[.*]]><\/listing>" \

source-highlight \
    --gen-version \
    --doc \
    --css="hl.css" \
    --out-format=xhtml \
    --src-lang=cpp \
    < test.cpp \
    > test.html
