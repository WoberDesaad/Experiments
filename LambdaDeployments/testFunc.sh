#!/bin/bash

RESPONSE=`aws lambda invoke --function-name lambdajenkins test.txt`

if [[ $RESPONSE == *"FunctionError"* ]]; then
	echo Function Error
	exit 1
fi
echo Function Success
