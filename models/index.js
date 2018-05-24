const path = require('path');

// Load ORM
const Sequelize = require('sequelize');


// To use SQLite data base:
//    DATABASE_URL = sqlite:quiz.sqlite
// To use  Heroku Postgres data base:
//    DATABASE_URL = postgres://user:passwd@host:port/database

const url = process.env.DATABASE_URL || "sqlite:quiz.sqlite";

const sequelize = new Sequelize(url);

// Import the definition of the Quiz Table from quiz.js
sequelize.import(path.join(__dirname, 'quiz'));

// Import the definition of the Tips Table from tip.js
sequelize.import(path.join(__dirname,'tip'));

// Import the definition of the Users Table from user.js
sequelize.import(path.join(__dirname,'user'));

<<<<<<< HEAD
=======
// Import the definition of the Attachments Table from attachment.js
sequelize.import(path.join(__dirname,'attachment'));

>>>>>>> practica6
// Session
sequelize.import(path.join(__dirname,'session'));


// Relation between models

<<<<<<< HEAD
const {quiz, tip, user} = sequelize.models;
=======
const {quiz, tip, attachment, user} = sequelize.models;
>>>>>>> practica6

tip.belongsTo(quiz);
quiz.hasMany(tip);

// Relation 1-to-N between User and Quiz:
user.hasMany(quiz, {foreignKey: 'authorId'});
quiz.belongsTo(user, {as: 'author', foreignKey: 'authorId'});
<<<<<<< HEAD
=======

// Relation 1-to-1 between Quiz and Attachment
attachment.belongsTo(quiz);
quiz.hasOne(attachment);

// Relation 1-to-1 between Quiz and User:
//    A User has many favourite quizzes.
//    A quiz has many fans (the users who have marked it as favorite)
quiz.belongsToMany(user, {
    as: 'fans',
    through: 'favourites',
    foreignKey: 'quizId',
    otherKey: 'userId'
});

user.belongsToMany(quiz, {
    as: 'favouriteQuizzes',
    through: 'favourites',
    foreignKey: 'userId',
    otherKey: 'quizId'
});
sequelize.sync()
.then(() => console.log('Data Bases created successfully'))
.catch(error => {
    console.log("Error creating the data base tables:", error);
    process.exit(1);
});
>>>>>>> practica6

module.exports = sequelize;
