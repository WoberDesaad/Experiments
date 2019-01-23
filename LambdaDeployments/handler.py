import json
import datetime


def handler(event, context):
    current_time = datetime.datetime.now().time()
    body = {
        "message": "Hello Bob, the current time is " + str(current_time)
    }

    response = {
        "statusCode": 200,
        "body": json.dumps(body)
    }

    return response
