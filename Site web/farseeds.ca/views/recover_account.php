<!--subscribe.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Subscription page of the website for Roots of Shadows -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Récupération du compte</title>
	<meta charset="utf-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
</head>
<body>
	<?php require_once("Layout/topmenu.php"); ?>
	<div class="body">
		<div class="form form-login">
			<div class="img-box img-form">
				<img src="Images/roots_logo.png">
			</div>
			<h3>Réinitialiser le mot de passe</h3>
			<form id="formEmail" method="POST" action="login.html">
				<input type="text" name="username" class="field" placeholder="Username or email">
				<input type="submit" name="btnNext" value="Next">
			</form>

			<!-- Remove this HR when the php is done -->
			<hr>

			<!-- Handle this with PHP (step-by-step #2) -->
			<form id="formQuestion" method="POST" action="login.html">
				<label id="SecurityQuestion">Here is your question?</label>
				<input type="text" name="SecurityAnswer" class="field" placeholder="Answer">
				<input type="submit" name="btnReset" value="Reset">
			</form>

			<!-- Handle this with PHP (step-by-step #3) -->
			<h3>Le mot de passe à été réinitialisé avec succès!</h3>
			<h4>Votre mot de passe temporaire est <span class="generated-password">CksOm23tY0</span></h4>
			<h5>Assurez-vous de changer ce mot de passe le plus rapidement possible. Personne d'autre que vous ne devrait avoir votre mot de passe. Personne d'autre que vous ne devrait connaitre la réponse à votre question pour la récupération du compte.</h5>
		</div>
	</div>
	<?php include_once("Layout/footer.php"); ?>
</body>
</html>
