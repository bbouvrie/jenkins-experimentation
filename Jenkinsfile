pipeline {
  agent any
  stages {
    stage('build') {
      agent {
        node {
          label 'qt'
        }

      }
      steps {
        echo 'This is where building the source code happens'
      }
    }
    stage('test') {
      agent {
        node {
          label 'qt'
        }

      }
      steps {
        echo 'This is where the tests are being executed'
      }
    }
  }
  triggers {
    pollSCM('*/5 * * * *')
  }
}