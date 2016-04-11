(function() {
  'use strict';

  module.exports = function(grunt) {

    grunt.initConfig({

      watch: {

        upload: {
          files: ['*.c', 'input', 'Makefile', 'lib/*'],
          tasks: ['sftp:upload']
        }

      },

      secret: grunt.file.readJSON('.secret.json'),
      sftp: {
        upload: {
          files: {
            './': ['*.c', 'input', 'Makefile', 'lib/*']
          },
          options: {
            path: '/home/join/dev/hw2',
            host: 'localhost',
            username: '<%= secret.username %>',
            password: '<%= secret.password %>',
            port: 2222
          }
        }
      }

    });

    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-ssh');

  };
  
})();