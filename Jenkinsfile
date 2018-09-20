pipeline {
  agent {
	label 'qt'
  }
  stages {
    stage('build') {
      steps {
        echo 'BUILD: Poging 3'
      }
    }
    stage('test') {
      steps {
        echo 'This is where the tests are being executed'
      }
    }
  }
  triggers {
    pollSCM('*/5 * * * *')
  }
}