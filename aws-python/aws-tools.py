#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""Aws command line and automation tool
    -Describe all Security Groups
    -Create a new Security Group
"""

import click
from bucket import BucketManager
from security_group import SecurityGroupManager
from iam import IAMManager


@click.group()
def cli():
    """Cli tool for AWS."""
    pass

@cli.group()
def bucket():
    """Bucket tool for AWS"""
    pass

@cli.group()
def security_group():
    """Security Group tool for AWS"""
    pass

@cli.group()
def iam():
    """IAM tool for AWS"""
    pass

@iam.command()
def list():
    IAMManager.list_users()

@bucket.command()
def list(bucket_name=None):
    """List all buckets"""
    if bucket_name:
        pass
    else:
        bucket_iterator = BucketManager.all_buckets()
        for bucket in bucket_iterator.all():
            print(bucket.name)

if __name__ == "__main__":
    cli()


