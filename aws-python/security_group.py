#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""Aws command line and automation tool
    -Describe all Security Groups
    -Create a new Security Group
"""

import boto3, json, time, click, mimetypes
from botocore.exceptions import ClientError
from hashlib import md5
from functools import reduce
from pathlib import Path

class SecurityGroupManager:

    def describe_security_groups():
        """Describes Security Groups."""
        ec2 = boto3.client('ec2')
    
        try:
            response = ec2.describe_security_groups();
            for sg in response['SecurityGroups']:
                for k in sg.keys():
                    if sg[k]:
                        print(k, " - ", sg[k])
        except ClientError as e:
            print(e)

    def make_test_security_group():
        """Makes a test security group."""
        ec2 = boto3.client('ec2')
        vpcs = ec2.describe_vpcs()
        vpc_id = vpcs['Vpcs'][0]['VpcId']
        response = ""

        try:
            response = ec2.create_security_group(
                    GroupName="TestGroup",
                    Description="SG Created from Boto3",
                    VpcId=vpc_id)
            sg_id = response['GroupId']
            print('A Sg %s was created in VPC %s.' % (sg_id, vpc_id))

            response = ec2.authorize_security_group_ingress(
                    GroupId=sg_id,
                    IpPermissions=[{
                        'IpProtocol': 'tcp',
                        'FromPort': 22,
                        'ToPort': 22,
                        'IpRanges': [{'CidrIp': '0.0.0.0/0'}]}
                        ])
            print(response)
        except ClientError as e:
            print(e)


