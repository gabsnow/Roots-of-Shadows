<!--login.php
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/07/10 (Hugo)
	Description: Login page of the website for Roots of Shadows -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Connexion</title>
	<meta charset="utf-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
</head>
<body>
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require("/$root/public/layout/topmenu.php");
	?>

	<div class="body">
		<div class="form form-login filterWrapper dark gold-border">
			<div class="img-box img-form">
				<img src="/public/images/roots_logo.png">
			</div>
			<form  method="POST" action="/index.php?action=login">
				<input type="text" name="username" class="field" placeholder="Pseudonyme ou courriel" required autofocus>
				<input type="password" name="password" class="field" placeholder="Mot de passe" required>
				<input type="submit" name="SubmitLogin" value="Se connecter à Roots of Shadows">
				<!--<label class="recover"><a href="/recover_account">Mot de passe oublié ?</a></label>-->
			</form>
			<?php if(!empty($msg)) { ?>
				<p class="centext red"><?=$msg?></p> <?php
			} ?>
		</div>
	</div>

	<?php include("$root/public/layout/footer.php");?>
</body>
</html>
