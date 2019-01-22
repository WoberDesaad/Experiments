pipeline {
  agent any
  stages {
    stage('build') {
      steps { 
        sh 'cd LAB8_QUAD && make'
      }
    }
    stage('test') {
      steps {
        dir('LAB8_QUAD'){
          sh './QUAD_COMPRESS test.png 100'
          sh './QUAD_COMPRESS test.png 50'
          sh './QUAD_COMPRESS test.png 25'
          sh './QUAD_COMPRESS test.png 12'
          sh './QUAD_COMPRESS test.png 0'
        }	   
        dir('LambdaDeploy'){
          sh 'zip function.zip handler.py'
        } 
      }
    }
    stage('deploy') {
      steps {
        dir('LambdaDeploy'){
          sh 'aws lambda create-function --function-name lambdajenkins --zip-file fileb://function.zip --handler handler.handler --runtime python3.7 --role arn:aws:iam::820315430153:role/test-lambdaIAMRole-8X3C9F220RGG'
        }
      }
    }
  }
}
