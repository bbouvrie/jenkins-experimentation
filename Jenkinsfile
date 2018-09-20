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
        echo 'BUILD: Ping 2'
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