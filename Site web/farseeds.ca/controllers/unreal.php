<?php
// unreal.php
// web api to retrieve the data needed in unreal
// author: Gabriel Bourgeois
// creation date: 22/10/2019

$root = realpath($_SERVER["DOCUMENT_ROOT"]);
require_once("$root/controllers/unrealcontroller.php");

if(isset($_GET["playerName"])) {
  $_GET["playerName"] = urldecode($_GET["playerName"]);
}

if(isset($_GET["request"])) {
  switch ($_GET["request"]) {
    case "dialogs":
      getDialogs();
      break;
    case "enemies":
      getEnemies();
      break;
    case "lastQuest":
      if(isset($_GET["playerName"]))
        getLastQuest($_GET["playerName"]);
      break;
    case "login":
      if(isset($_GET["username"]) && isset($_GET["password"]))
        login($_GET["username"], $_GET["password"]);
      break;
    case "player":
      if(isset($_GET["username"]))
        getPlayer($_GET["username"]);
      break;
    case "playerExists":
      if(isset($_GET["playername"]))
        playerExists($_GET["playername"]);
      break;
    case "quests":
      getQuests();
      break;
    case "questTasks":
      getQuestTasks();
      break;
    case "taskProgress":
      if(isset($_GET["playerName"]))
        getTaskProgress($_GET["playerName"]);
      break;
  }
}

if(isset($_GET["action"])) {
  switch ($_GET["action"]) {
    case "acceptQuest":
      if(isset($_GET["pass"]) && isset($_GET["playerName"]) && isset($_GET["questId"]))
        acceptQuest($_GET["pass"], $_GET["playerName"], $_GET["questId"]);
      break;
    case "completeQuest":
      if(isset($_GET["pass"]) && isset($_GET["playerName"]) && isset($_GET["questId"]))
        completeQuest($_GET["pass"], $_GET["playerName"], $_GET["questId"]);
      break;
    case "createPlayer":
      if(isset($_GET["playerName"]) && isset($_GET["username"]) && isset($_GET["password"]))
        createPlayer($_GET["playerName"], $_GET["username"], $_GET["password"]);
      break;
    case "setCinematic":
      if(isset($_GET["playerName"]))
        setPlayerCinematic($_GET["playerName"]);
      break;
    case "setTaskProgress":
      if(isset($_GET["pass"]) && isset($_GET["playerName"]) && isset($_GET["taskId"]) && isset($_GET["qty"]))
      setTaskProgress($_GET["pass"], $_GET["playerName"], $_GET["taskId"], $_GET["qty"]);
      break;
    case "turnQuest":
      if(isset($_GET["pass"]) && isset($_GET["playerName"]) && isset($_GET["questId"]))
        turnQuest($_GET["pass"], $_GET["playerName"], $_GET["questId"]);
      break;
    case "updatePlayer":
      if(isset($_GET["pass"]) && isset($_GET["name"]) && isset($_GET["hp"]) && isset($_GET["maxHp"]) && isset($_GET["mp"]) && isset($_GET["maxMp"]) && isset($_GET["str"]) && isset($_GET["pos"]) &&
         isset($_GET["money"]) && isset($_GET["int"]) && isset($_GET["agi"]) && isset($_GET["stealth"]) && isset($_GET["exp"]) && isset($_GET["viewed"]))
        updatePlayer($_GET["pass"], $_GET["name"], $_GET["hp"], $_GET["maxHp"], $_GET["mp"], $_GET["maxMp"], $_GET["str"], $_GET["pos"], $_GET["money"], $_GET["int"], $_GET["agi"], $_GET["stealth"], $_GET["exp"], $_GET["viewed"]);
      break;
  }
}
