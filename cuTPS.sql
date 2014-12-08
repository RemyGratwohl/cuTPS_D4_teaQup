-- You can run this script in the sqlite client
-- Download client from here: http://www.sqlite.org/download.html
-- Enter the following commands: 
-- .open cuTPSDB
-- .read cuTPS.sql 
-- Make sure this file is in the same directory as the client 
-- or provide the link to the directory

begin transaction;

-- Stores in the information related to users
drop table if exists users; -- 'user' is a reserved keyword

-- Stores the information related to courses
drop table if exists course;

-- Stores the relation between users and the courses
drop table if exists course_user;

-- Stores information related to a term
drop table if exists term;

-- Stores more generic information TODO
drop table if exists contentItem;

-- Stores TODO
drop table if exists book;

-- Stores information relative to the chapter
drop table if exists chapter; 

-- Stores information relative to a chapter section
drop table if exists chapterSection;

-- Stores the purchasing details of every purchasable item
drop table if exists purchasingDetails; 

-- TODO
drop table if exists course_book;

-- =========================== Table Creation ===========================

create table users (
	userid integer NOT NULL primary key, -- UserID for students can be their student#
	name varchar(60) NOT NULL,
	usertype integer NOT NULL -- 0 for student, 1 for content manager, 2 for admin
);

create table term (
	termid integer NOT NULL primary key,
	semester varchar(1) NOT NULL, -- F - Fall, W - Winter, S - Summer
	term_year integer NOT NULL
);

create table course (
	courseid integer NOT NULL primary key,
	name varchar(60) NOT NULL,
	termid integer NOT NULL,
	FOREIGN KEY(termid) REFERENCES term(termid) ON DELETE CASCADE
);

--creating the Table called contentItem

create table contentItem (
	contentid integer NOT NULL primary key,
	title varchar(60) NOT NULL,
	isbn varchar(60) NOT NULL,
	courseid integer,
	FOREIGN KEY(courseid) REFERENCES course(courseid) ON DELETE CASCADE
);

create table course_user (
	userid integer NOT NULL,
	coid integer NOT NULL,
	PRIMARY KEY(userid, courseid)
);

create table purchasingDetails (
	purchaseid integer NOT NULL primary key AUTOINCREMENT,
	price real NOT NULL, 
	vendor varchar(60) NOT NULL,
	contentid integer,
	FOREIGN KEY(contentid) REFERENCES contentItem(contentid) ON DELETE CASCADE

); 

create table book (
	bid integer NOT NULL primary key, 
	subtitle varchar(60),
	authors varchar(80) NOT NULL,
	website varchar(80),
	year_publish integer NOT NULL,
	publisher varchar(60) NOT NULL,
	citation varchar(80),
	picturelink varchar(80),
	FOREIGN KEY(bid) REFERENCES contentItem(contentid) ON DELETE CASCADE
);

create table chapter (
	chid integer NOT NULL primary key,
	bookid integer NOT NULL,  
	chapter_num integer NOT NULL,
	FOREIGN KEY(chid) REFERENCES contentItem(contentid) ON DELETE CASCADE,
	FOREIGN KEY(bookid) REFERENCES book(contentid) ON DELETE CASCADE
);

create table chapterSection (
	sectionid integer NOT NULL primary key,
	chapterid integer NOT NULL, 
	section_num real NOT NULL,
	pageRange varchar(40),
	FOREIGN KEY(chapterid) REFERENCES chapter(contentid) ON DELETE CASCADE,
	FOREIGN KEY(sectionid) REFERENCES contentItem(contentid) ON DELETE CASCADE
);

create table course_book ( 
	courseid integer NOT NULL,
	contentid integer NOT NULL,
	FOREIGN KEY(contentid) REFERENCES book(contentid) ON DELETE CASCADE,
	FOREIGN KEY(courseid) REFERENCES course(courseid) ON DELETE CASCADE,
	PRIMARY KEY(courseid, contentid)
);

-- TODO sales data
--inserting data into the table names
--insert into names (name) values('');

insert into users (userid, name, usertype) values (100845934, 'Timmy Tortoise', 0);
insert into users (userid, name, usertype) values (100945234, 'Harold DaHare', 0);
insert into users (userid, name, usertype) values (100945932, 'Matilda', 1);

insert into term (termid, semester, term_year) values (1, 'F', 2014);

insert into course (courseid, name, termid) values (1, 'CHEM1004: Generic Chemistry', 1);
insert into course (courseid, name, termid) values (2, 'COMP2304: Correcting Software Engineering Textbooks', 1);

insert into course_user (userid, coid) values (845934, 1);
insert into course_user (userid, coid) values (945234, 2);

insert into contentItem (contentid, title, isbn, courseid) values (1, 'Chemistry', '978-0-470-15579-0', 1);
insert into contentItem (contentid, title, isbn, courseid) values (2, 'Object-Oriented Software Engineering', '978-0-470-123422-0', 2);
insert into contentItem (contentid, title, isbn, courseid) values (3, 'Fundamental Concepts of Chemistry', '978-0-470-15579-0-01', 1);
insert into contentItem (contentid, title, isbn, courseid) values (4, 'The Behaviour of Gases', '978-0-470-15579-0-02', 1);
insert into contentItem (contentid, title, isbn, courseid) values (5, 'Energy and Its Conservation', '978-0-470-15579-0-03', 1);
insert into contentItem (contentid, title, isbn, courseid) values (6, 'Atoms and Light', '978-0-470-15579-0-04', 1);
insert into contentItem (contentid, title, isbn, courseid) values (7, 'Introduction to Software Engineering', '978-0-470-123422-0-01', 2);
insert into contentItem (contentid, title, isbn, courseid) values (8, 'Atoms, Molecules and Compounds', '978-0-470-15579-0-01-01', 1);
insert into contentItem (contentid, title, isbn, courseid) values (9, 'Measurements in Chemistry', '978-0-470-15579-0-01-02', 1);
insert into contentItem (contentid, title, isbn, courseid) values (10, 'Chemical Problem Solving', '978-0-470-15579-0-01-03', 1);
insert into contentItem (contentid, title, isbn, courseid) values (11, 'Counting Atoms: The Mole', '978-0-470-15579-0-01-04', 1);
insert into contentItem (contentid, title, isbn, courseid) values (12, 'Amounts of Compounds', '978-0-470-15579-0-01-05', 1);
insert into contentItem (contentid, title, isbn, courseid) values (13, 'Aqueous Solutions', '978-0-470-15579-0-01-06', 1);
insert into contentItem (contentid, title, isbn, courseid) values (14, 'Pressure', '978-0-470-15579-0-02-01', 1);
insert into contentItem (contentid, title, isbn, courseid) values (15, 'Types of Energy', '978-0-470-15579-0-03-01', 1);
insert into contentItem (contentid, title, isbn, courseid) values (16, 'Characteristics of Atoms', '978-0-470-15579-0-04-01', 1);
insert into contentItem (contentid, title, isbn, courseid) values (17, 'Introduction: Software Engineering Failures', '978-0-470-123422-0-01-01', 2);
insert into contentItem (contentid, title, isbn, courseid) values (18, 'What is Software Engineering?', '978-0-470-123422-0-01-02', 2);
insert into contentItem (contentid, title, isbn, courseid) values (19, 'Software Engineering Concepts', '978-0-470-123422-0-01-03', 2);
insert into contentItem (contentid, title, isbn, courseid) values (20, 'Software Engineering Development Activities', '978-0-470-123422-0-01-04', 2);
insert into contentItem (contentid, title, isbn, courseid) values (21, 'Managing Software Development', '978-0-470-123422-0-01-05', 2);

insert into book (bid, subtitle, authors, publisher, website, year_publish) values (1, 'Canadian Edition', 'Burk & Co.', 'Wiley', 'www.wiley.com', 2010);
insert into book (bid, subtitle, authors, publisher, website, year_publish) values (2, 'Using UML, Patterns, and JAVA', 'Bern D. Bruegge, Allen H. Dutoit, etc', 'Pearson', 'www.pearson.com', 2011);

insert into chapter (chid, bookid, chapter_num) values (3, 1, 1);
insert into chapter (chid, bookid, chapter_num) values (4, 1, 2);
insert into chapter (chid, bookid, chapter_num) values (5, 1, 3);
insert into chapter (chid, bookid, chapter_num) values (6, 1, 4);

insert into chapter (chid, bookid, chapter_num) values (7, 2, 1);

insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (8, 3, 1.1, 'Pages: 4 - 5');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (9, 3, 1.2, 'Pages: 6 - 12');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (10, 3, 1.3, 'Pages: 13 - 14');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (11, 3, 1.4, 'Pages: 15 - 18');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (12, 3, 1.5, 'Pages: 19 - 27');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (13, 3, 1.6, 'Pages: 28 - 67');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (14, 4, 2.1, 'Pages: 70 - 71');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (15, 5, 3.1, 'Pages: 130 - 140');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (16, 6, 4.1, 'Pages: 194 - 195');

insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (17, 7, 1.1, '');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (18, 7, 1.2, '');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (19, 7, 1.3, '');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (20, 7, 1.4, '');
insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (21, 7, 1.5, '');

-- no longer needed
-- insert into purchasingDetails (purchaseid, price, vendor, contentid) values (0, -1.00, 'NOT FOR SALE');
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (0, 209.99, 'Carleton University', 1);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (1, 300.99, 'TakinYourDeets', 2);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (2, 19.99, 'TakinYourDeets', 7);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (3, 9.99, 'TakinYourDeets', 17);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (4, 9.99, 'TakinYourDeets', 18);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (5, 9.99, 'TakinYourDeets', 19);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (6, 9.99, 'TakinYourDeets', 20);
insert into purchasingDetails (purchaseid, price, vendor, contentid) values (7, 9.99, 'TakinYourDeets', 21);


commit;

