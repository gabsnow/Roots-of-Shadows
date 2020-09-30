<?php
  function initiate_session() {
    session_start();

    if(!isset($_SESSION["username"])){
      $root = realpath($_SERVER["DOCUMENT_ROOT"]);
      require_once("$root/views/login.php");
      exit();
    }
  }
