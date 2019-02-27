#!/bin/bash

REAL_PATH=$(dirname $(realpath ${0}))

# the name of the root folder is the exe name
NAME=$(basename $(realpath ${REAL_PATH}))

export NAME
