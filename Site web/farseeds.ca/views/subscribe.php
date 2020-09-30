<!--subscribe.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Subscription page of the website for Roots of Shadows -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Création de compte</title>
	<meta charset="utf-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
</head>
<body>
	<!-- Top Menu -->
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require_once("$root/public/layout/topmenu.php");
	?>

	<div class="body">
		<div class="form form-subscribe filterWrapper dark gold-border">
			<div class="img-box img-form">
				<img src="/public/images/roots_logo.png">
			</div>
			<form method="POST" action="index.php?action=subscribe" name="subscribe">
				<div class="flexput">
					<input type="text" name="firstName" class="field shared" placeholder="Prénom" required  pattern="[^0-9]{2,18}" title="Le prénom doit être entre 2 et 18 caractères et ne doit pas contenir de chiffre." autofocus value="">
					<input type="text" name="lastName" class="field" placeholder="Nom" required pattern="[^0-9]{2,18}" title="Le nom doit être entre 2 et 18 caractères et ne doit pas contenir de chiffre." value="">
				</div>

				<div class="flexput">
					<!-- Birth day -->
					<input type="number" name="birthDay" class="field first" placeholder="Jour de naissance" required min="1" max="31" value="">
					<!-- Month -->
					<div class="select-container">
						<select name="birthMonth" required placeholder="month" class="field">
							<option value="" disabled selected><span>Mois</span></option>
							<option value="1">Janvier</option>
							<option value="2">Février</option>
							<option value="3">Mars</option>
							<option value="4">Avril</option>
							<option value="5">Mai</option>
							<option value="6">Juin</option>
							<option value="7">Juillet</option>
							<option value="8">Aout</option>
							<option value="9">Septembre</option>
							<option value="10">Octobre</option>
							<option value="11">Novembre</option>
							<option value="12">Décembre</option>
						</select>
					</div>
					<!-- Year -->
					<input type="number" name="birthYear" class="field" placeholder="Année" min="1900" max="2019" required value="">
				</div>
				<!--<br>-->
				<input type="text" name="username" class="field" placeholder="Pseudonyme" required pattern="^[a-zA-Z0-9]{6,18}$" title="Le pseudonyme doit être entre 6 et 18 caractères et ne contenir aucun caractère spécial, exemple: DocteurBeaver." value="">
				<input type="email" name="email" class="field" placeholder="Courriel" required pattern="^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$" title="Entrez une adresse courriel valide, exemple: doctorbeaver@rootsofshadows.com." value="">
				<input type="password" name="password" class="field" placeholder="Mot de passe" required pattern=".{4,18}" title="Le mot de passe doit être entre 4 et 18 caractères." value="">
				<input type="password" name="confirmPassword" class="field" placeholder="Confirmer le mot de passe" required pattern=".{4,18}" title="Password must be between 4 and 18 characters." value="">
				<!--<br>-->
				<input type="text" name="securityQuestion" class="field" placeholder="Question de sécurité" required pattern=".{4,60}" title="La question de sécurité doit être entre 4 et 60 caractères." value="">
				<input type="text" name="securityAnswer" class="field" placeholder="Votre réponse" required pattern=".{1,60}" title="La réponse doit être 60 caractères ou moins." value="">
				<input type="submit" name="SubmitSubscribe" value="Créer un compte">
			</form>
		</div>
	</div>

	<!-- Footer -->
	<?php include_once("$root/public/layout/footer.php"); ?>

	<script type="text/javascript">
		// how to manually show a validity message:
		// document.forms[0].elements[0].value = "a"; == refill the field with old value
		// document.forms[0].elements[0].reportValidity("HGMM"); == pop up the validity message
	</script>

</body>
</html>
