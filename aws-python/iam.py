#!/usr/bin/python3
# -*- coding: utf-8 -*-

import boto3, json, time, click, mimetypes
from botocore.exceptions import ClientError
from hashlib import md5
from functools import reduce
from pathlib import Path


class IAMManager:
    """Manages IAM."""

    def __init__(self, session):
        """Create a FileManager object."""
        self.session = session

    def list_users():
        iam = boto3.client('iam')
        print(iam.list_users())

