<!--armory.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Armory page of the website for Roots of Shadows: the armory is used to find
	a player within the game and see his equipement, achivements, skills, etc. -->

	<!DOCTYPE html>
	<html>
	<head>
		<title>Roots of Shadows - Histoire</title>
		<meta charset="utf-8">
	  	<meta name="viewport" content="width=device-width, initial-scale=1">
			<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
			<link rel="stylesheet" href="/public/css/all.min.css">
	  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
			<link rel="stylesheet" type="text/css" href="/public/css/about.css">
	</head>
	<body>
		<?php
			$root = realpath($_SERVER["DOCUMENT_ROOT"]);
			require_once("$root/public/layout/topmenu.php");
		?>

		<div class="body">
			<div class="filterWrapper full-width min-full-height flex vertical font-white">
				<h1 class="centext">Téléchargement</h1>

					<div class="flex horinzontal filterWrapper dark">
						<div class="flex big vertical about">
							<h2>Comment installer le jeu</h2>
							<div class="downloadStep">
								<div class="flex horinzontal">
									<div class="flex big vertical about">
										<h2>Étape #1</h2>
										<h5>Télécharger le jeu.</h5>
										<div class="centerButton">
											<button type="button" class="downloadButton">
												<b style="color:white; text-shadow: 1px 1px black;">Windows (x64)</b> <br>
												Version : 1.0
											</button>
										</div>
										Télécharger, puis enregistrer.
									</div>
									<div class="flex big vertical about">
										<h2>Étape #2</h2>
										<h5>Éxécuter l'installeur.</h5>
										<div class="centerButton">
											<img src="../public/images/DownloadStep2.png" alt="Étape3">
										</div>
										Suivre les étapes une à une.
									</div>
									<div class="flex big vertical about">
										<h2>Étape #3</h2>
										<h5>Ouvrir le jeu.</h5>
										<div class="centerButton">
											<img src="../public/images/DownloadStep2.png" alt="Étape3">
										</div>
										Ça y est! Il ne vous reste plus qu'à vous créer un personnage!
									</div>
								</div>
							</div>
						</div>


				</div>
			</div>
		</div>


		<?php include_once("$root/public/layout/footer.php"); ?>
	</body>
	</html>
