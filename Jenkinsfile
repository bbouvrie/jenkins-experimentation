pipeline {
  agent {
	label 'qt'
  }
  stages {
    stage('build') {
      steps {
		bat 'masterclass-jenkins-compile.bat'
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