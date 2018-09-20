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
        bat 'masterclass-jenkins-test'
      }
    }
  }
  triggers {
    pollSCM('*/5 * * * *')
  }
}