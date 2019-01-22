pipeline {
  agent any
  stages {
    stage('build') {
      steps { 
        sh 'cd ./LAB8_QUAD'
        sh 'pwd'
        sh 'ls'
        sh 'make'
      }
    }
    stage('test') {
      steps {
        sh './QUAD_COMPRESS test.png 100'
        sh './QUAD_COMPRESS test.png 50'
        sh './QUAD_COMPRESS test.png 25'
        sh './QUAD_COMPRESS test.png 12'
        sh './QUAD_COMPRESS test.png 0'
      }	    
    }
  }
}
