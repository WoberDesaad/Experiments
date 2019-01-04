import boto3, json, time
from botocore.exceptions import ClientError

def describe_security_groups():
    ec2 = boto3.client('ec2')

    try:
        response = ec2.describe_security_groups();
        for sg in response['SecurityGroups']:
            print(sg['Description'])
    except ClientError as e:
        print(e)


def make_test_security_group():
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




if __name__ == "__main__":
    describe_security_groups()
