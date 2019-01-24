import json
import datetime


def handler(event, context):
    current_time = datetime.datetime.now().time()
    body = {
        "message": str(current_time)
    }
    #Adding some comments. This will be different...

    response = {
        "statusCode": 200,
        "body": json.dumps(body)
    }

    return response
