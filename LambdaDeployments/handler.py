import json
import datetime
import boto3


def handler(event, context):
    current_time = datetime.datetime.now().time()
    body = {
        "message": str(current_time)
    }

    response = { 
        "statusCode": 200,
        "body": json.dumps(body)
    }

    return response
