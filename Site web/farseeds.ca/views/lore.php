<!--lore.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Lore page of the website for Roots of Shadows: the lore page contains the information
	about the game: classes, races, monster, the game story, etc. -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Histoire</title>
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

	<div class="body">
	</div>

	<?php include_once("$root/public/layout/footer.php"); ?>
</body>
</html>
