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
          sh 'cd LAB8_QUAD && ./QUAD_COMPRESS test.png 100'
          sh './QUAD_COMPRESS test.png 50'
          sh './QUAD_COMPRESS test.png 25'
          sh './QUAD_COMPRESS test.png 12'
          sh './QUAD_COMPRESS test.png 0'
        }	    
      }
    }
  }
}
