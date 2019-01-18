#!/usr/bin/ruby
# -*- coding: utf-8 -*-

require 'aws-sdk-iam'  # v2: require 'aws-sdk'
require 'date'
require 'cgi'


def get_key_age(key_creation_date)
	return (( Time.now - key_creation_date ) / 3600 / 24).floor
end


iam = Aws::IAM::Client.new(region: 'us-west-2')

iam.list_users.users.each do |user|
  name = user.user_name
  puts "For user #{name}"
  puts "  In groups:"

  iam.list_groups_for_user({user_name: name}).groups.each do |group|
    puts "    #{group.group_name}"
  end
  
  puts "  Policies:"
  
  iam.list_user_policies({user_name: name}).policy_names.each do |policy|
    puts "    #{policy}"
    
  end

  iam.list_attached_user_policies({user_name: name}).attached_policies.each do |policy|
    puts "    #{policy}"
  end

  iam.list_groups_for_user({user_name: name}).groups.each do |group|
    iam.list_attached_group_policies({group_name: group.group_name}).attached_policies.each do |policy|
      policy_arn = policy[:policy_arn]
      policy_version = iam.get_policy({policy_arn: policy_arn})[:policy][:default_version_id]
      puts "  #{CGI::unescape(iam.get_policy_version({ policy_arn: policy_arn, version_id: policy_version, })[:policy_version][:document])}"
    end
  end
  
  puts "  Access keys:"

  iam.list_access_keys({user_name: name}).access_key_metadata.each do |key|
    puts "    #{key.access_key_id} -- Age: #{get_key_age(key.create_date)} days"
  end
end

