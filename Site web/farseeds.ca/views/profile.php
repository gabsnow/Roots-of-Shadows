<!--profile.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Profile page for a user -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Mon compte</title>
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
		<div class="account flex vertical full-width filterWrapper dark slim-border">
			<h2 class="font-white centext">Mon compte</h2>

			<h3>Information personelle</h3>
			<div class="account-section flex horizontal">
				<div class="flex vertical">
					<label class="flex horizontal">
						<span>Prénom : </span>
						<span><?=$user["firstName"]?></span>
					</label>

					<label class="flex horizontal">
						<span>Nom : </span>
						<span><?=$user["lastName"] ?></span>
					</label>

					<label class="flex horizontal">
						<span>Date de naissance : </span>
						<span><?=$user["birthdate"] ?></span>
					</label>
				</div>
			</div>


			<h3>Authentification</h3>
			<div class="account-section flex horizontal">
				<div class="flex vertical all">
					<label class="flex horizontal">
						<span>Pseudonyme : </span>
						<span class="account-data"><?=$user["username"]?></span>
						<div class="account btn" onclick="enableFieldEdit(event)"><i class="fas fa-edit"></i></div>
					</label>

					<label class="flex horizontal">
						<span>Courriel : </span>
						<span class="account-data"><?=$user["email"]?></span>
						<!-- <div class="account btn"><i class="fas fa-edit"></i></div>  -->
					</label>

					<label class="flex horizontal">
						<span class="text-right">Mot de passe : </span>
						<span>********</span>
						<input class="hide account-data" type="hidden" value="<?=$user["password"]?>">
						<div class="account btn pass" onclick="enableFieldEdit(event)"><i class="fas fa-edit"></i></div>
					</label>

				</div>
			</div>

			<h3>Sécurité</h3>
			<div class="account-section flex horizontal">
				<div class="flex vertical">
					<label class="flex horizontal">
						<span>Question : </span>
						<span class="account-data"><?=$user["securityQuestion"]?></span>
						<div class="account btn" onclick="enableFieldEdit(event)"><i class="fas fa-edit"></i></div>
					</label>

					<label class="flex horizontal">
						<span>Réponse : </span>
						<span class="account-data"><?=$user["securityAnswer"] ?></span>
						<input class="hide account-data" type="hidden" value="********">
						<div class="account btn pass" onclick="enableFieldEdit(event)"><i class="fas fa-edit"></i></div>
					</label>
				</div>
			</div>
		</div>

		<?php
			if(empty($player)) { ?>
		<div class="account flex vertical full-width filterWrapper dark slim-border">
			<p style="text-align: center; font-style: italic; color: white">Vous n'avez pas de personnage pour l'instant. Créez-vous en un pour commencer votre aventure dès maintenant!</p>
		</div> <?php
		 } ?>
	</div>

	<?php include_once("$root/public/layout/footer.php"); ?>

	<script type="text/javascript" src="/public/js/profile.js"></script>

</body>
</html>
