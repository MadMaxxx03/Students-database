// Лаба 3 2.cpp: определяет точку входа для приложения.
//

#include "Лаба 3 2.h"

#include <fstream>
#include <string>

using namespace std;

const char* STUDENT_FILE = "Student.txt";
const char* GROUP_FILE = "Group.txt";

struct Student {
	char surname[40];
	int age;
	int mark;
	char group[10];
};

struct Group {
	char group[10];
	char teacher[40];
	bool fulltime;
};

Student* createStudent(char ** groups_list_ptr) {
	Student* newStudent = new Student;
	cout << "Enter information" << endl;
	cout << "Surname >> ";
	cin >> newStudent->surname;
	cout << "Age >> ";
	cin >> newStudent->age;
	cout << "Mark >> ";
	cin >> newStudent->mark;
	cout << "Group >> ";
	cin >> newStudent->group;
	return newStudent;
}

Group* createGroup(char** groups_list_ptr, int count_g) {
	Group* newGroup = new Group;
	cout << "Enter information" << endl;
	cout << "Group >> ";
	cin >> newGroup->group;
	groups_list_ptr[count_g-1] = newGroup->group;
	cout << "Teacher >> ";
	cin >> newGroup->teacher;
	cout << "Is full-time education: 1 = yes 0 = no >> ";
	cin >> newGroup->fulltime;
	return newGroup;
}

void readFromStudents(int count_s) {
	ifstream readDataBase_S;
	readDataBase_S.open(STUDENT_FILE);
	int i = 0;
	char cstring_s[100];
	while ((!readDataBase_S.eof()) && (i < count_s)) {
		readDataBase_S.getline(cstring_s, sizeof(Student));
		cout << cstring_s << endl;;
	}
	readDataBase_S.close();
}

void readFromGroups(int count_g) {
	ifstream readDataBase_G;
	readDataBase_G.open(GROUP_FILE);
	int i = 0;
	char cstring_s[40];
	while ((!readDataBase_G.eof()) && (i < count_g)) {
		for (int j = 0; j < 3; j++) {
			readDataBase_G.getline(cstring_s, sizeof(Student), ' ');
			cout << cstring_s << " ";
		}
		i++;
	}

	readDataBase_G.close();
}

void Sort(int count_g, int count_s) {
	string delimiter = " ";
	string token;
	size_t pos = 0;
	int i = 0;

	cin.ignore();
	string SELECT;
	getline(cin, SELECT);
	string* SELECT_ptr = new string[5];

	while ((pos = SELECT.find(delimiter)) != string::npos) {
		token = SELECT.substr(0, pos);
		SELECT_ptr[i] = token;
		i++;
		SELECT.erase(0, pos + delimiter.length());
	}
	SELECT_ptr[i] = SELECT;

	//cin.ignore();
	pos = 0;
	i = 0;
	string FROM;
	getline(cin, FROM);
	string* FROM_ptr = new string[2];

	while ((pos = FROM.find(delimiter)) != string::npos) {
		token = FROM.substr(0, pos);
		FROM_ptr[i] = token;
		i++;
		FROM.erase(0, pos + delimiter.length());
	}
	FROM_ptr[i] = FROM;

	//cin.ignore();
	pos = 0;
	i = 0;
	string WHERE;
	getline(cin, WHERE);
	string* WHERE_ptr = new string[4];

	while ((pos = WHERE.find(delimiter)) != string::npos) {
		token = WHERE.substr(0, pos);
		WHERE_ptr[i] = token;
		i++;
		WHERE.erase(0, pos + delimiter.length());
	}
	WHERE_ptr[i] = WHERE;

	int S_r_count = 0;
	int S_r_true_count = 0;
	if ((SELECT_ptr[0] == "SELECT") && (FROM_ptr[0] == "FROM") && (WHERE_ptr[0] == "WHERE")) {
		if (FROM_ptr[1] == "Students") {
			for (int i = 1; i < 5; i++) {
				if (SELECT_ptr[i] != "") {
					S_r_count++;
					if ((SELECT_ptr[i] == "surname") || (SELECT_ptr[i] == "mark") || (SELECT_ptr[i] == "age") || (SELECT_ptr[i] == "group")) {
						S_r_true_count++;
					}
				}
				else {
					break;
				}
			}

			//S_list{surname; age; mark; group}
			//WHERE_ptr{WHERE; поле; условие; цифра}
			//SELECT_ptr{SELECT; условие; ...}
			/*
			SELECT surname group
			FROM Students
			WHERE age < 20
			*/

			if (S_r_count == S_r_true_count) {
				if ((WHERE_ptr[1] == "surname") || (WHERE_ptr[1] == "mark") || (WHERE_ptr[1] == "age") || (WHERE_ptr[1] == "group")) {
					if ((WHERE_ptr[2] == "<") || (WHERE_ptr[2] == ">")) {
						if ((WHERE_ptr[1] == "age") || (WHERE_ptr[1] == "mark")) {
							string S_list[4];
							ifstream readDataBase_S;
							readDataBase_S.open(STUDENT_FILE);
							int i_count = 0;
							char cstring_s[40];
							while ((!readDataBase_S.eof()) && (i_count < count_s)) {
								readDataBase_S.getline(cstring_s, sizeof(Student));
								string cstring_str = string(cstring_s);
								delimiter = " ";
								pos = 0;
								int k = 0;

								while ((pos = cstring_str.find(delimiter)) != string::npos) {
									token = cstring_str.substr(0, pos);
									S_list[k] = token;
									k++;
									cstring_str.erase(0, pos + delimiter.length());
								}
								S_list[k] = cstring_str;
								if (WHERE_ptr[1] == "age") {
									if (WHERE_ptr[2] == "<") {
										if (stoi(S_list[1]) < stoi(WHERE_ptr[3])) {
											for (int i = 1; i < S_r_count + 1; i++) {
												if (SELECT_ptr[i] == "surname") {
													cout << S_list[0] << " ";
												}
												else if (SELECT_ptr[i] == "age") {
													cout << S_list[1] << " ";
												}
												else if (SELECT_ptr[i] == "mark") {
													cout << S_list[2] << " ";
												}
												else if (SELECT_ptr[i] == "group") {
													cout << S_list[3] << " ";
												}
											}
											cout << "" << endl;
										}
									}
									else {
										if (stoi(S_list[1]) > stoi(WHERE_ptr[3])) {
											for (int i = 1; i < S_r_count + 1; i++) {
												if (SELECT_ptr[i] == "surname") {
													cout << S_list[0] << " ";
												}
												else if (SELECT_ptr[i] == "age") {
													cout << S_list[1] << " ";
												}
												else if (SELECT_ptr[i] == "mark") {
													cout << S_list[2] << " ";
												}
												else if (SELECT_ptr[i] == "group") {
													cout << S_list[3] << " ";
												}
											}
											cout << "" << endl;
										}
									}
								}
								else {
									if (WHERE_ptr[2] == "<") {
										if (stoi(S_list[2]) < stoi(WHERE_ptr[3])) {
											for (int i = 1; i < S_r_count + 1; i++) {
												if (SELECT_ptr[i] == "surname") {
													cout << S_list[0] << " ";
												}
												else if (SELECT_ptr[i] == "age") {
													cout << S_list[1] << " ";
												}
												else if (SELECT_ptr[i] == "mark") {
													cout << S_list[2] << " ";
												}
												else if (SELECT_ptr[i] == "group") {
													cout << S_list[3] << " ";
												}
											}
											cout << "" << endl;
										}
									}
									else {
										if (stoi(S_list[2]) > stoi(WHERE_ptr[3])) {
											for (int i = 1; i < S_r_count + 1; i++) {
												if (SELECT_ptr[i] == "surname") {
													cout << S_list[0] << " ";
												}
												else if (SELECT_ptr[i] == "age") {
													cout << S_list[1] << " ";
												}
												else if (SELECT_ptr[i] == "mark") {
													cout << S_list[2] << " ";
												}
												else if (SELECT_ptr[i] == "group") {
													cout << S_list[3] << " ";
												}
											}
											cout << "" << endl;
										}
									}
								}

								i_count++;
							}
							readDataBase_S.close();
						}
						else {
							cout << "Wrong request, try again 5" << endl;
						}
					}
					else if (WHERE_ptr[2] == "=") {
						if ((WHERE_ptr[1] == "surname") || (WHERE_ptr[1] == "age") || (WHERE_ptr[1] == "mark") || (WHERE_ptr[1] == "group")) {
							//S_list{surname; age; mark; group}
							//WHERE_ptr{WHERE; поле; условие; цифра}
							//SELECT_ptr{SELECT; условие; ...}
							string S_list[4];
							ifstream readDataBase_S;
							readDataBase_S.open(STUDENT_FILE);
							int i_count = 0;
							char cstring_s[40];
							while ((!readDataBase_S.eof()) && (i_count < count_s)) {
								readDataBase_S.getline(cstring_s, sizeof(Student));
								string cstring_str = string(cstring_s);
								delimiter = " ";
								pos = 0;
								int k = 0;

								while ((pos = cstring_str.find(delimiter)) != string::npos) {
									token = cstring_str.substr(0, pos);
									S_list[k] = token;
									k++;
									cstring_str.erase(0, pos + delimiter.length());
								}
								S_list[k] = cstring_str;
								if (WHERE_ptr[1] == "surname") {
									if (string(S_list[0]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < S_r_count + 1; i++) {
											if (SELECT_ptr[i] == "surname") {
												cout << S_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "age") {
												cout << S_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "mark") {
												cout << S_list[2] << " ";
											}
											else if (SELECT_ptr[i] == "group") {
												cout << S_list[3] << " ";
											}
										}
										cout << "" << endl;
									}
								}
								else if (WHERE_ptr[1] == "age") {
									if (string(S_list[1]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < S_r_count + 1; i++) {
											if (SELECT_ptr[i] == "surname") {
												cout << S_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "age") {
												cout << S_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "mark") {
												cout << S_list[2] << " ";
											}
											else if (SELECT_ptr[i] == "group") {
												cout << S_list[3] << " ";
											}
										}
										cout << "" << endl;
									}
								}
								else if (WHERE_ptr[1] == "mark") {
									if (string(S_list[2]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < S_r_count + 1; i++) {
											if (SELECT_ptr[i] == "surname") {
												cout << S_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "age") {
												cout << S_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "mark") {
												cout << S_list[2] << " ";
											}
											else if (SELECT_ptr[i] == "group") {
												cout << S_list[3] << " ";
											}
										}
										cout << "" << endl;
									}
								}
								else {
									if (string(S_list[3]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < S_r_count + 1; i++) {
											if (SELECT_ptr[i] == "surname") {
												cout << S_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "age") {
												cout << S_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "mark") {
												cout << S_list[2] << " ";
											}
											else if (SELECT_ptr[i] == "group") {
												cout << S_list[3] << " ";
											}
										}
										cout << "" << endl;
									}
								}

								i_count++;
								
							}
							readDataBase_S.close();
						}
						else {
							cout << "Wrong request, try again 6" << endl;
						}
					}
					else {
						cout << "Wrong request, try again 7" << endl;
					}
				}
				else {
					cout << "Wrong request, try again 1" << endl;
				}
			}
			else {
				cout << "Wrong request, try again 2" << endl;
			}
		}
		else if (FROM_ptr[1] == "Groups") {
		//S_list{surname; age; mark; group}
			//WHERE_ptr{WHERE; поле; условие; цифра}
			//SELECT_ptr{SELECT; условие; ...}
			int G_r_count = 0;
			int G_r_true_count = 0;
				for (int i = 1; i < 4; i++) {
					if (SELECT_ptr[i] != "") {
						G_r_count++;
						if ((SELECT_ptr[i] == "teacher") || (SELECT_ptr[i] == "fulltime") || (SELECT_ptr [i] == "group")) {
							G_r_true_count++;
						}
					}
				}
				if (G_r_count == G_r_true_count) {
					if ((WHERE_ptr[1] == "teacher") || (WHERE_ptr[1] == "fulltime") || (WHERE_ptr[1] == "group")) {
						if (WHERE_ptr[2] == "=") {
							string G_list[3];
							ifstream readDataBase_G;
							readDataBase_G.open(GROUP_FILE);
							int i_count = 0;
							char cstring_g[40];
							/*char group[10];
							char teacher[40];
							bool fulltime;*/
							while ((!readDataBase_G.eof()) && (i_count < count_g)) {
								readDataBase_G.getline(cstring_g, sizeof(Student));
								string cstring_str = string(cstring_g);
								delimiter = " ";
								pos = 0;
								int k = 0;
								while ((pos = cstring_str.find(delimiter)) != string::npos) {
									token = cstring_str.substr(0, pos);
									G_list[k] = token;
									k++;
									cstring_str.erase(0, pos + delimiter.length());
								}
								G_list[k] = cstring_str;
								if (WHERE_ptr[1] == "group") {
									if (string(G_list[0]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < G_r_count + 1; i++) {
											if (SELECT_ptr[i] == "group") {
												cout << G_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "teacher") {
												cout << G_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "fulltime") {
												cout << G_list[2] << " ";
											}
										}
										cout << "" << endl;
									}
								}
								else if (WHERE_ptr[1] == "teacher") {
									if (string(G_list[1]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < G_r_count + 1; i++) {
											if (SELECT_ptr[i] == "group") {
												cout << G_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "teacher") {
												cout << G_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "fulltime") {
												cout << G_list[2] << " ";
											}
										}
										cout << "" << endl;
									}
								}
								else {
									if (string(G_list[2]) == string(WHERE_ptr[3])) {
										for (int i = 1; i < G_r_count + 1; i++) {
											if (SELECT_ptr[i] == "group") {
												cout << G_list[0] << " ";
											}
											else if (SELECT_ptr[i] == "teacher") {
												cout << G_list[1] << " ";
											}
											else if (SELECT_ptr[i] == "fulltime") {
												cout << G_list[2] << " ";
											}
										}
										cout << "" << endl;
									}
								}

								i_count++;

							}
							readDataBase_G.close();
						}
						else {
							cout << "Wrong request, try again 7" << endl;
						}
					}
					else {
						cout << "Wrong request, try again 1" << endl;
					}
				}
				else {
					cout << "Wrong request, try again 2" << endl; 
				}
		}
		else {
			cout << "Wrong request, truy again 3" << endl;
		}
	 }
	else {
	cout << "Wrong request, try again 4" << endl;
	cout << SELECT_ptr[0] << " " << FROM_ptr[0] << " " << WHERE_ptr[0];
	}
}

void Join(int count_g, int count_s) {
	cout << "Enter request >>" << endl;
	string delimiter = " ";
	string token;
	size_t pos = 0;
	int i = 0;

	cin.ignore();
	string SELECT_J;
	getline(cin, SELECT_J);
	string SELECT_J_ptr[7];

	while ((pos = SELECT_J.find(delimiter)) != string::npos) {
		token = SELECT_J.substr(0, pos);
		SELECT_J_ptr[i] = token;
		i++;
		SELECT_J.erase(0, pos + delimiter.length());
	}
	SELECT_J_ptr[i] = SELECT_J;

	string jn;
	getline(cin, jn);

	string List_S[4];
	string List_G[3];
	string S0[10];
	string S1[10];
	string S2[10];
	string S3[10];
	string G0[10];
	string G1[10];
	string G2[10];

	ifstream readDataBase_S;
	readDataBase_S.open(STUDENT_FILE);
	int i_count = 0;
	char cstring_s[40];
	while ((!readDataBase_S.eof()) && (i_count < count_s)) {
		readDataBase_S.getline(cstring_s, sizeof(Student));
		string cstring_str = string(cstring_s);
		delimiter = " ";
		pos = 0;
		int k = 0;

		while ((pos = cstring_str.find(delimiter)) != string::npos) {
			token = cstring_str.substr(0, pos);
			List_S[k] = token;
			k++;
			cstring_str.erase(0, pos + delimiter.length());
		}
		List_S[k] = cstring_str;

		S0[i_count] = List_S[0];
		S1[i_count] = List_S[1];
		S2[i_count] = List_S[2];
		S3[i_count] = List_S[3];
		i_count++;
	}
	readDataBase_S.close();

	ifstream readDataBase_G;
	readDataBase_G.open(GROUP_FILE);
	i_count = 0;
	char cstring_g[40];
	while ((!readDataBase_G.eof()) && (i_count < count_g)) {
		readDataBase_G.getline(cstring_g, sizeof(Student));
		string cstring_str = string(cstring_g);
		delimiter = " ";
		pos = 0;
		int k = 0;
		while ((pos = cstring_str.find(delimiter)) != string::npos) {
			token = cstring_str.substr(0, pos);
			List_G[k] = token;
			k++;
			cstring_str.erase(0, pos + delimiter.length());
		}
		List_G[k] = cstring_str;

		G0[i_count] = List_G[0];
		G1[i_count] = List_G[1];
		G2[i_count] = List_G[2];
		
		i_count++;
	}
	readDataBase_S.close();

	int L_count = 0;
	int L_true_count = 0;
	for (int i = 1; i < 7; i++) {
		if (SELECT_J_ptr[i] != "") {
			L_count++;
			if ((SELECT_J_ptr[i] == "teacher") || (SELECT_J_ptr[i] == "fulltime") || (SELECT_J_ptr[i] == "group") || (SELECT_J_ptr[i] == "surname") || (SELECT_J_ptr[i] == "age") || (SELECT_J_ptr[i] == "mark")) {
				L_true_count++;
			}
		}
	}
	if (L_count == L_true_count) {
		int r = 2;
		while (true) {
			cout << "If you want to add condition: enter 1; else 0:" << endl;
			cin >> r;
			if ((r == 0) || (r == 1)) {
				break;
			}
		}
		if (r == 0) {
			//SELECT_J_ptr[i] ={"surname" "age" "group" "mark" "teacher" "fulltime")
			string m[6];
			for (int i = 0; i < count_s; i++) {
				m[0] = S0[i];
				m[1] = S1[i];
				m[2] = S2[i];
				m[3] = S3[i];
				for (int j = 0; j < count_g; j++) {
					if (G0[j] == m[3]) {
						m[4] = G1[j];
						m[5] = G2[j];
						break;
					}
				}
				for (int i = 1; i < L_true_count + 1; i++) {
					if (SELECT_J_ptr[i] == "surname") {
						cout << m[0] << " ";
					}
					else if (SELECT_J_ptr[i] == "age") {
						cout << m[1] << " ";
					}
					else if (SELECT_J_ptr[i] == "mark") {
						cout << m[2] << " ";
					}
					else if (SELECT_J_ptr[i] == "group") {
						cout << m[3] << " ";
					}
					else if (SELECT_J_ptr[i] == "teacher") {
						cout << m[4] << " ";
					}
					else {
						cout << m[5] << " ";
					}
				}
				cout << "" << endl;
			}
			
		}
		else {
			cout << "Input condition" << endl;
			pos = 0;
			i = 0;

			cin.ignore();
			string WHERE_J;
			getline(cin, WHERE_J);
			string WHERE_J_ptr[4];

			while ((pos = WHERE_J.find(delimiter)) != string::npos) {
				token = WHERE_J.substr(0, pos);
				WHERE_J_ptr[i] = token;
				i++;
				WHERE_J.erase(0, pos + delimiter.length());
			}
			WHERE_J_ptr[i] = WHERE_J;

			if ((WHERE_J_ptr[1] == "teacher") || (WHERE_J_ptr[1] == "fulltime") || (WHERE_J_ptr[1] == "group") || (WHERE_J_ptr[1] == "surname") || (WHERE_J_ptr[1] == "age") || (WHERE_J_ptr[1] == "mark")) {
				if (WHERE_J_ptr[2] == "<") {
					if (WHERE_J_ptr[1] == "age") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (stoi(m[1]) < stoi(WHERE_J_ptr[3])) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
							
						}
					}
					else if (WHERE_J_ptr[1] == "mark") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (stoi(m[2]) < stoi(WHERE_J_ptr[3])) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}

						}
					}
					else {
						cout << "Wrong request, try again 1.4" << endl;
					}
				}
				else if (WHERE_J_ptr[2] == ">") {
					if (WHERE_J_ptr[1] == "age") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (stoi(m[1]) < stoi(WHERE_J_ptr[3])) {
								for (int i = 1; i > L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}

						}
					}
					else if (WHERE_J_ptr[1] == "mark") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (stoi(m[2]) > stoi(WHERE_J_ptr[3])) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}

						}
					}
					else {
						cout << "Wrong request, try again 1.5" << endl;
					}
				}
				else if (WHERE_J_ptr[2] == "=") {
					if (WHERE_J_ptr[1] == "surname"){
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[0] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
					else if (WHERE_J_ptr[1] == "age") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[1] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
					else if (WHERE_J_ptr[1] == "mark") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[2] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
					else if (WHERE_J_ptr[1] == "group") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[3] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
					else if (WHERE_J_ptr[1] == "age") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[1] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
					else if (WHERE_J_ptr[1] == "teacher") {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[4] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
					else {
						string m[6];
						for (int i = 0; i < count_s; i++) {
							m[0] = S0[i];
							m[1] = S1[i];
							m[2] = S2[i];
							m[3] = S3[i];
							for (int j = 0; j < count_g; j++) {
								if (G0[j] == m[3]) {
									m[4] = G1[j];
									m[5] = G2[j];
									break;
								}
							}
							if (m[5] == WHERE_J_ptr[3]) {
								for (int i = 1; i < L_true_count + 1; i++) {
									if (SELECT_J_ptr[i] == "surname") {
										cout << m[0] << " ";
									}
									else if (SELECT_J_ptr[i] == "age") {
										cout << m[1] << " ";
									}
									else if (SELECT_J_ptr[i] == "mark") {
										cout << m[2] << " ";
									}
									else if (SELECT_J_ptr[i] == "group") {
										cout << m[3] << " ";
									}
									else if (SELECT_J_ptr[i] == "teacher") {
										cout << m[4] << " ";
									}
									else {
										cout << m[5] << " ";
									}
								}
								cout << "" << endl;
							}
						}
					}
				}
				else {
					cout << "Wrong request, try again 1.3" << endl;
				}
			}
			else {
				cout << "Wrong request, try again 1.2" << endl;
			}
		}
	}
	else {
		cout << "Wrong request, try again 1.1" << endl;
	}

	
}

int main()
{
	int count_s = 0;
	int count_g = 0;

	char* groups_list[15];
	char** groups_list_ptr = groups_list;
	bool is_rightgroup;

	ofstream Students_f;
	ofstream Groups_f;

	int option = 0;
	while (option != 7) {
		cout << "" << endl;
		cout << "Choose option:" << endl;
		cout << "1 - Add Student" << endl;
		cout << "2 - Add Group" << endl;
		cout << "3 - Show Students" << endl;
		cout << "4 - Show Groups" << endl;
		cout << "5 - Spesial option 1" << endl;
		cout << "6 - Spesial option 2" << endl;
		cout << "7 - Stop" << endl;
		cin >> option;
		cout << "" << endl;

		if (option == 1) {
			is_rightgroup = false;
			Student* newStudent = createStudent(groups_list_ptr);
			 
			for (int i = 0; i < count_g; i++) {
				if (string(newStudent->group) == string(groups_list[i])) {
					is_rightgroup = true;
					break;
				}
				else {

				}
			}

			if (is_rightgroup) {
				count_s++;
				Students_f.open(STUDENT_FILE, ofstream::app);
				Students_f << newStudent->surname << " " << newStudent->age << " ";
				Students_f << newStudent->mark << " " << newStudent->group << endl;;
				Students_f.close();
			}
			else {
				cout << "Wrong group, input student again" << endl;
			}
		}
		else if (option == 2) {
			count_g++;
			Groups_f.open(GROUP_FILE, ofstream::app);
			Group* newGroup = createGroup(groups_list_ptr, count_g);
			Groups_f << newGroup->group << " " << newGroup->teacher << " ";
			if (newGroup->fulltime == 0) {
				Groups_f << "No" << endl;
			}
			else {
				Groups_f << "Yes" << endl;
			}
			Groups_f.close();
		}
		else if (option == 3) {
			if (count_s != 0) {
				readFromStudents(count_s);
			}
			else {
				cout << "Its nothing to read" << endl;
			}
		}
		else if (option == 4) {
			if (count_g != 0) {
				readFromGroups(count_g);
			}
			else {
				cout << "Its nothing to read" << endl;
			}
		}
		else if (option == 5) {
			cout << "Input request >>" << endl;
			Sort(count_g, count_s);
		}
		else if (option == 6) {
			Join(count_g, count_s);
		}

	}

	Groups_f.open(GROUP_FILE, ios::out);
	Groups_f.close();

	Students_f.open(STUDENT_FILE, ios::out);
	Students_f.close();

	return 0;
}

 