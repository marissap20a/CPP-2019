#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

Student::Student(std::string student_id, std::string name) :
    id(student_id), name(name){}
	

std::string Student::get_id(){
	return id;
}

std::string Student::get_name(){
	return name;
}
void Student::addCourse(std::string course_id){
	course_ids.push_back(course_id);
}
void Student::listCourses(){
	if(course_ids.size() == 0){
		cout << "No Courses" << endl;
	}
	else{
		for(int i = 0; i < course_ids.size(); ++i){
			cout << course_ids[i]<< endl;
		}
	}
}