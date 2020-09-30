<?php
// index.php
// auteur: Gabriel Bourgeois
// date de création: 4 septembre 2019
// router pour la structure MVC du site

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

$root = realpath($_SERVER["DOCUMENT_ROOT"]);
require_once("$root/controllers/controller.php");

session_start();

if(!empty($_POST)) {
  foreach ($_POST as $key => $value) {
    $_POST[$key] = htmlspecialchars($value);
  }
}

if (!isset($_GET["page"]) && !isset($_GET["action"])) {
  loadHomePage();
}

if(isset($_GET["page"])) {
  switch($_GET["page"]) {
    case "download":
      loadDownloadPage();
      break;
    case "about":
      loadAboutPage();
      break;
    case "report":
      loadReportPage();
      break;
    case "credits":
      loadCreditsPage();
      break;
    case "home":
      loadHomePage();
      break;
    case "login":
      if(isset($_GET["failed"]))
        loadLoginPage("Utilisateur ou mot de passe invalide.");
      else if (isset($_GET["unconfirmed"]))
        loadLoginPage("Ce compte n'a pas encore été vérifié par courriel.");
      else
        loadLoginPage();
      break;
    case "logout":
      logout();
      break;
    case "lore":
      loadLorePage();
      break;
    case "media":
      loadMediaPage();
      break;
    case "news":
      loadNewsPage();
      break;
    case "profile":
      if(isset($_SESSION["username"]))
        loadProfilePage($_SESSION["username"]);
      else
        showError("Error", "No user to show");
      break;
    case "subscribe":
      loadSubscribePage();
      break;
    default:
      loadHomePage();
      break;
  }
}

if(isset($_GET["Objet"]) && isset($_GET["Bogue"])){//submit bug
  if(trim($_GET["Objet"]," 	\n") != "" && trim($_GET["Bogue"]," 	\n") != ""){
    if(isset($_SESSION["username"])){

      $email1 = "h_lamoureux@aol.com";
      $email2 = "gabsnow18@gmail.com";
      $email3 = "vikdreamz@gmail.com";
      $email4 = "babou625@gmail.com";

      $headers = "From: bugs-sender@farseeds.ca" . "\n" . 'Content-Type: text/plain; charset=utf-8' . "\r\n";

      $txt = wordwrap("Message de : " . $_SESSION["username"] . "\n" . $_GET["Bogue"], 70);

      mail($email1, $_GET["Objet"], $txt, $headers);
      mail($email2, $_GET["Objet"], $txt, $headers);
      mail($email3, $_GET["Objet"], $txt, $headers);
      mail($email4, $_GET["Objet"], $txt, $headers);

      echo "<div style='color:lightgreen'>Merci de nous aider à améliorer Roots of Shadows!</div>";
    }
    else{
      echo "<div style='color:red'>Si le bouton est désactiver, c'est pour une raison</div>";
    }

  }
  else{
    echo "<div style='color:red'>Message de bogue non valide!</div>";
  }
}
else{
  echo "<div style='color:red'>Message de bogue non valide!</div>" ;
}

if(isset($_GET["action"])) {
  switch ($_GET["action"]) {
    case "login":
      if(isset($_POST["SubmitLogin"])) {
        login($_POST["username"], $_POST["password"]);
      }
      else
        showError("Error", "No user to log in.");
      break;
    case "submitPost":
      if(isset($_POST["SubmitNewPost"]) && isset($_SESSION["id"]))
        createPost($_SESSION["id"], $_POST["title"], $_POST["content"]);
      else
        showError("Error", "No post submitted");
      break;
    case "subscribe":
      if(isset($_POST["SubmitSubscribe"])) {
        if($_POST["password"] == $_POST["confirmPassword"] /* && le username n'est pas deja pris */ )
          createUser($_POST["firstName"], $_POST["lastName"], $_POST["birthDay"],
                     $_POST["birthMonth"], $_POST["birthYear"], $_POST["username"],
                     $_POST["email"], $_POST["password"], $_POST["securityQuestion"],
                     $_POST["securityAnswer"]);
        else
          showError("Woops", "Passwords do not match.");
      }
      else
        showError("Woops", "No user to subscribe.");
      break;
    case "updateMember":
      if(isset($_POST["SubmitUpdateUser"])) {
        $password = $_POST["password"];

        if($password[0] != "$" && strlen($password) < 50)
          $password = password_hash($password, PASSWORD_DEFAULT);

        updateUser($_SESSION["id"], $_POST["username"], $_POST["email"], $password, $_POST["securityQuestion"], $_POST["securityAnswer"]);
      }
      else
        showError("Error", "No user to update");
      //echo '<script language="javascript">';
      //echo 'alert("message successfully sent")';
      //echo '</script>';
      echo("<pre>");
      print_r($_POST);
      echo("</pre>");

      break;
      case "emailConfirm":
      if(isset($_GET["pseudo"])){
        if(isset($_GET["confirm"])){
          confirmEmail($_GET["pseudo"], $_GET["confirm"]);
        }
      }
      break;

    default:
      showError("ERROR", "Nope");
      break;
  }
}
