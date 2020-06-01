#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "Student.h"
#include "AttendanceRecord.h"
#include "Course.h"
#include "Date.h"

using namespace std;

void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
      students.push_back(Student(uin, name));
    }
  }
}
void School::listStudents(){
	if(students.size() == 0){
		cout << "No Students" << endl;
	}
	else{
		for(int i = 0; i < students.size() ; ++i){
			cout << students[i].get_id() << "," << students[i].get_name() << endl;
		}
	}
}

void School::addCourses(std::string filename) {
	ifstream ifs(filename);
	if(!ifs.is_open()) {
		cout << "Unable to open file: " << filename << endl;
		return;
	}
	
	string line;
	//while (!ifs.eof()) {
	while(getline(ifs, line)) {
    //cout << "READING: " << line << endl;
	
    istringstream ss(line);
    
	string course_id;
    getline(ss, course_id, ',');
	
	string shour;
	string smin;
    getline(ss, shour, ':');
	getline(ss, smin, ',');
	int hour1 = stoi(shour);
	int min1 = stoi(smin);
	
	string ehour;
	string emin;
	getline(ss, ehour, ':');
	getline(ss, emin, ',');
	int hour2 = stoi(ehour);
	int min2 = stoi(emin);
	
	string courses_temp;
	getline(ss, courses_temp);
	/*
	while(getline(ss, courses_temp, ',')){
		if(courses_temp.find(" and") == 0){
			courses_temp = courses_temp.substr(courses_temp.find(" and")+4);
		}
		if (!ss.fail()) {
			courses.push_back(Course(course_id, courses_temp, Date(hour1,min1,0), Date(hour2,min2,0)));
		}
		
		cout << "courses: " << courses_temp << endl;
	}
	*/
	if (!ss.fail()) {
		courses.push_back(Course(course_id, courses_temp, Date(hour1,min1), Date(hour2,min2)));
	}
	//ss.clear();
	//ss.str("");
 
}
 
}


void School::listCourses(){
	if(courses.size() == 0){
		cout << "No Courses" << endl;
	}
	else{
		for(int i = 0; i < courses.size() ; ++i){
			cout << setfill ('0') << setw (2);
			cout << courses[i].getID() << "," << setfill ('0') << setw (2) << (courses[i].getStartTime()).getHour() << ":" << setfill ('0') << setw (2) << (courses[i].getStartTime()).getMin() <<
			","<< setfill ('0') << setw (2) << (courses[i].getEndTime()).getHour() << ":" << setfill ('0') << setw (2) << (courses[i].getEndTime()).getMin() << "," << courses[i].getTitle() << endl;
		}
	}
}




void School::addAttendanceData(std::string filename){
	
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  
  string line;
  while (getline(ifs, line)) {
    istringstream ss(line);
	
    string year;
    getline(ss, year, '-');
    int year1 = stoi(year);
	
	string month;
    getline(ss, month, '-');
    int month1 = stoi(month);
	
	string day;
    getline(ss, day, ' ');
    int day1= stoi(day);
	
	string hour;
    getline(ss, hour, ':');
	int hour1 = stoi(hour);
	
	string min;
    getline(ss, min, ':');
	int min1 = stoi(min);
	
	string sec;
    getline(ss, sec, ',');
	int sec1 = stoi(sec);
	
	string course_id;
	getline(ss, course_id, ',');
	
	string student_id;
	getline(ss, student_id);
	
    if (!ss.fail()) {
		// 1. Find course c in courses
		// 2. once you've found the course, invoke its addAttendanceRecord member function
		for(int i = 0; i < courses.size(); ++i){
			if(courses[i].getID() == course_id){
				courses[i].addAttendanceRecord(AttendanceRecord(course_id, student_id, Date(year1, month1, day1, hour1, min1, sec1)));
			}
			// in courses class vector<AttendanceRecord> attendanceRecords;
		}
		//c.addAttendanceRecord(AttendanceRecord(course_id, student_id, Date(year1, month1, day1, hour1, min1, sec1)));
    }
  }
}


void School::outputCourseAttendance(std::string course_id){
	if(courses.size() == 0){
		cout << "No Records" << endl;
	}
	else{
		for(int i = 0; i < courses.size() ; ++i){
			//cout << courses[i].getID() << "/"<< course_id << endl;
			if(courses[i].getID() == course_id){
				courses[i].outputAttendance();
			}
		}
	}
	
	
	
	
}
void School::outputStudentAttendance(std::string student_id, std::string course_id){
	bool isValidCourse = false;
	if(courses.size() == 0){
		cout << "No Records" << endl;
	}
	else{
		for(int i = 0; i < courses.size() ; ++i){
			if(courses[i].getID() == course_id){
				isValidCourse = true;
				courses[i].outputAttendance(student_id);
			}
		}
		if(isValidCourse == false){
			cout << "No Records" << endl;
		}
	}
}