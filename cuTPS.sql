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
	contentid integer NOT NULL primary key AUTOINCREMENT,
	title varchar(60) NOT NULL,
	courseid integer,
	FOREIGN KEY(courseid) REFERENCES course(courseid) ON DELETE CASCADE
);

create table course_user (
	userid integer NOT NULL,
	courseid integer NOT NULL,
	PRIMARY KEY(userid, courseid)
);

create table purchasingDetails (
	purchaseid integer NOT NULL primary key,
	price real NOT NULL, 
	vendor varchar(60) NOT NULL,
	contentid integer,
	FOREIGN KEY(contentid) REFERENCES contentItem(contentid) ON DELETE CASCADE

); 

create table book (
	contentid integer NOT NULL primary key, 
	subtitle varchar(60),
	authors varchar(80) NOT NULL,
	ISBN varchar(60) NOT NULL, 
	website varchar(80),
	year_publish integer NOT NULL,
	publisher varchar(60) NOT NULL,
	citation varchar(80),
	picturelink varchar(80),
	FOREIGN KEY(contentid) REFERENCES contentItem(contentid) ON DELETE CASCADE
);

create table chapter (
	chapterid integer NOT NULL primary key,
	bookid integer NOT NULL,  
	chapter_num integer NOT NULL,
	ISBN varchar(60) NOT NULL,
	FOREIGN KEY(chapterid) REFERENCES contentItem(contentid) ON DELETE CASCADE,
	FOREIGN KEY(bookid) REFERENCES book(contentid) ON DELETE CASCADE
);

create table chapterSection (
	sectionid integer NOT NULL primary key,
	chapterid integer NOT NULL, 
	section_num real NOT NULL,
	pageRange varchar(40),
	ISBN varchar(60) NOT NULL,
	FOREIGN KEY(chapterid) REFERENCES chapter(contentid) ON DELETE CASCADE,
	FOREIGN KEY(sectionid) REFERENCES contentItem(contentid) ON DELETE CASCADE
);

-- TODO sales data
--inserting data into the table names
--insert into names (name) values('');

insert into users (userid, name, usertype) values (845934, 'Timmy Tortoise', 0);
insert into users (userid, name, usertype) values (945234, 'Harold DaHare', 0);

insert into term (termid, semester, term_year) values (1, 'F', 2014);

insert into course (courseid, name, termid) values (1, 'CHEM1004: Generic Chemistry', 1);
insert into course (courseid, name, termid) values (2, 'COMP2304: Correcting Software Engineering Textbooks', 1);

insert into course_user (userid, courseid) values (845934, 1);
insert into course_user (userid, courseid) values (945234, 2);

insert into contentItem (contentid, title, courseid) values (1, 'Chemistry', 1);
insert into contentItem (contentid, title, courseid) values (2, 'Object-Oriented Software Engineering', 2);
insert into contentItem (contentid, title, courseid) values (3, 'Fundamental Concepts of Chemistry', 1);
insert into contentItem (contentid, title, courseid) values (4, 'The Behaviour of Gases', 1);
insert into contentItem (contentid, title, courseid) values (5, 'Energy and Its Conservation', 1);
insert into contentItem (contentid, title, courseid) values (6, 'Atoms and Light', 1);
insert into contentItem (contentid, title, courseid) values (7, 'Introduction to Software Engineering', 2);
insert into contentItem (contentid, title, courseid) values (8, 'Atoms, Molecules and Compounds', 1);
insert into contentItem (contentid, title, courseid) values (9, 'Measurements in Chemistry', 1);
insert into contentItem (contentid, title, courseid) values (10, 'Chemical Problem Solving', 1);
insert into contentItem (contentid, title, courseid) values (11, 'Counting Atoms: The Mole', 1);
insert into contentItem (contentid, title, courseid) values (12, 'Amounts of Compounds', 1);
insert into contentItem (contentid, title, courseid) values (13, 'Aqueous Solutions', 1);
insert into contentItem (contentid, title, courseid) values (14, 'Pressure', 1);
insert into contentItem (contentid, title, courseid) values (15, 'Types of Energy', 1);
insert into contentItem (contentid, title, courseid) values (16, 'Characteristics of Atoms', 1);
insert into contentItem (contentid, title, courseid) values (17, 'Introduction: Software Engineering Failures', 2);
insert into contentItem (contentid, title, courseid) values (18, 'What is Software Engineering?', 2);
insert into contentItem (contentid, title, courseid) values (19, 'Software Engineering Concepts', 2);
insert into contentItem (contentid, title, courseid) values (20, 'Software Engineering Development Activities', 2);
insert into contentItem (contentid, title, courseid) values (21, 'Managing Software Development', 2);

insert into book (contentid, subtitle, authors, publisher, ISBN, website, year_publish) values (1, 'Canadian Edition', 'Burk & Co.', 'Wiley', '978-0-470-15579-0', 'www.wiley.com', 2010);
insert into book (contentid, subtitle, authors, publisher, ISBN, website, year_publish) values (2, 'Using UML, Patterns, and JAVA', 'Bern D. Bruegge, Allen H. Dutoit, etc', 'Pearson', '978-0-470-123422-0', 'www.pearson.com', 2011);

insert into chapter (chapterid, bookid, chapter_num, ISBN) values (3, 1, 1, '978-0-470-15579-0-01');
insert into chapter (chapterid, bookid, chapter_num, ISBN) values (4, 1, 2, '978-0-470-15579-0-02');
insert into chapter (chapterid, bookid, chapter_num, ISBN) values (5, 1, 3, '978-0-470-15579-0-03');
insert into chapter (chapterid, bookid, chapter_num, ISBN) values (6, 1, 4, '978-0-470-15579-0-04');

insert into chapter (chapterid, bookid, chapter_num, ISBN) values (7, 2, 1, '978-0-470-123422-0-01');

insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (8, 3, 1.1, 'Pages: 4 - 5', '978-0-470-15579-0-01-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (9, 3, 1.2, 'Pages: 6 - 12', '978-0-470-15579-0-01-02');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (10, 3, 1.3, 'Pages: 13 - 14', '978-0-470-15579-0-01-03');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (11, 3, 1.4, 'Pages: 15 - 18', '978-0-470-15579-0-01-04');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (12, 3, 1.5, 'Pages: 19 - 27', '978-0-470-15579-0-01-05');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (13, 3, 1.6, 'Pages: 28 - 67', '978-0-470-15579-0-01-06');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (14, 4, 2.1, 'Pages: 70 - 71', '978-0-470-15579-0-02-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (15, 5, 3.1, 'Pages: 130 - 140', '978-0-470-15579-0-03-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (16, 6, 4.1, 'Pages: 194 - 195', '978-0-470-15579-0-04-01');

insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (17, 7, 1.1, '', '978-0-470-123422-0-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (18, 7, 1.2, '', '978-0-470-123422-0-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (19, 7, 1.3, '', '978-0-470-123422-0-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (20, 7, 1.4, '', '978-0-470-123422-0-01');
insert into chapterSection (sectionid, chapterid, section_num, pageRange, ISBN) values (21, 7, 1.5, '', '978-0-470-123422-0-01');

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

