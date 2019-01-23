#!/bin/bash


echo Looking for Function \'lambdajenkins\'

aws lambda get-function --function-name lambdajenkins

if [[ $? == 0 ]]
then
	echo Function Exists...Updating
	aws lambda update-function-code --region us-east-1 --function-name lambdajenkins --zip-file fileb://function.zip 
else
	echo Function does not exist...Creating
	aws lambda create-function --region us-east-1 --function-name lambdajenkins --zip-file fileb://function.zip --handler handler.handler --runtime python3.7 --role arn:aws:iam::820315430153:role/test-lambdaIAMRole-8X3C9F220RGG
fi
