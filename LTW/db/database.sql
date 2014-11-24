DROP TABLE IF EXISTS User;

DROP TABLE IF EXISTS UserLogin;

DROP TABLE IF EXISTS UserQuery;

DROP TABLE IF EXISTS Answer;

DROP TABLE IF EXISTS UserAnswer;


CREATE TABLE User(
	idUser INTEGER PRIMARY KEY AUTOINCREMENT,
	username NVARCHAR2(20) NOT NULL,
	email NVARCHAR2(20) NOT NULL,
	password NVARCHAR2(20) NOT NULL
);

CREATE TABLE UserLogin(
	idUserLogin INTEGER PRIMARY KEY AUTOINCREMENT,
	idUser NUMBER  REFERENCES User(idUser),
	IPUser NVARCHAR2(20)
);


CREATE TABLE UserQuery(
	idUserQuery INTEGER PRIMARY KEY AUTOINCREMENT,
	idUser NUMBER  REFERENCES User(idUser),
	Question VARCHAR(200) NOT NULL
);


CREATE TABLE Answer(
	idAnswer INTEGER PRIMARY KEY AUTOINCREMENT,
	idUserQuery NUMBER  REFERENCES UserQuery(idUserQuery),
	Answerino VARCHAR(200) NOT NULL
);


CREATE TABLE UserAnswer(
	idUserAnswer INTEGER PRIMARY KEY AUTOINCREMENT,
	idUser NUMBER  REFERENCES User(idUser),
	idAnswer NUMBER  REFERENCES Answer(idAnswer),
	idUserQuery NUMBER  REFERENCES UserQuery(idUserQuery)
);

INSERT INTO User VALUES (1, 'cera', 'cera@asd.com', 'cera');
INSERT INTO UserLogin VALUES(1, 1, '172.22.128.225');