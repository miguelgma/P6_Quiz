'use strict';

module.exports = {
    up(queryInterface, Sequelize) {
        return queryInterface.addColumn(
            'quizzes',
            'authorId',
            {
                type: Sequelize.BOOLEAN,
                defaultValue: false
            }
        );
    },

    down(queryInterface, Sequelize) {
        return queryInterface.removeColumn('tips', 'accepted');
    }
};
