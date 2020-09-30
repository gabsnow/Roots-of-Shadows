// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestData.h"
// #include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

std::string QuestData::GetDialog(std::string nomNpc, int nbDialog) {

	//Select d.Dialog from Dialogs d
	//inner join NPCs n on d.idNPC = n.idNPC
	//where n.Name = nomNpc and d.Order = nbDialog;

	//MYSQL* mysql;

	//MYSQL_STMT* stmt;

	//int status;

	//mysql = mysql_init(NULL);

	///* connect to MariaDB server */
	//mysql_real_connect(mysql, "farseeds.ca", "pdo", "AUFq@42782Yf", "DB_Roots", 3306, NULL, 0);

	return "";
}
