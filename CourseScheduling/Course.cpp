#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"
#include "Student.h"
using namespace std;

Course::Course(std::string id, std::string title, Date startTime, Date endTime) :
	id(id), title(title), startTime(startTime), endTime(endTime) {}
	
std::string Course::getID(){
	return id;
}
std::string Course::getTitle(){
	return title;
}
Date Course::getStartTime(){
	return startTime;
}
Date Course::getEndTime(){
	return endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar){
	attendanceRecords.push_back(ar);
}

void Course::outputAttendance(){
	for(int i = 0; i < attendanceRecords.size(); ++i){
	cout << attendanceRecords[i].getDate().getDate() <<","<<attendanceRecords[i].getCourseID() << 
	","<< attendanceRecords[i].getStudentID() << endl;
	}
	
}
void Course::outputAttendance(std::string student_id){
	bool inRecords = false;
	for(int i = 0; i < attendanceRecords.size(); ++i){
		if(attendanceRecords[i].getStudentID() == student_id){
			inRecords = true;
			cout << attendanceRecords[i].getDate().getDate() <<","<<attendanceRecords[i].getCourseID() << 
			","<< attendanceRecords[i].getStudentID() << endl;
		}
	}
	if(inRecords == false){
		cout << "No Records" << endl;
	}
	
}