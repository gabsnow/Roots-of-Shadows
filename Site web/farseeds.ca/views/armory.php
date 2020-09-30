<!--armory.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Armory page of the website for Roots of Shadows: the armory is used to find
	a player within the game and see his equipement, achivements, skills, etc. -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Armurerie</title>
	<meta charset="utf-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
</head>
<body>
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require_once("$root/public/layout/topmenu.php");
	?>

	<div class="body-wrap">

	</div>

	<?php include_once("/$root/public/layout/footer.php"); ?>
</body>
</html>
