<!--report.php
	Author: Gabriel Bourgeois
	Creation date: 14/06/19
	Last editted: 14/06/19
	Description: Report page of the website for Roots of Shadows, used to report
  bugs to the developpers -->


<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Signaler une erreur</title>
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
		<div class="filterWrapper full-width min-full-height flex vertical font-white">
			<h1 class="centext">Signaler une erreur</h1>
				<div class="flex horinzontal filterWrapper dark">
					<div class="flex big vertical bugs">
						<h2>Formulaire</h2><br>
						<form action="../index.php" method="get" class="form bugs-form">

							<?php if(!isset($_SESSION["username"])) echo "<h4 style='color:red;'>Vous devez être connecté pour signaler une erreur.</h4>"; ?>
							<div class="flex vertical">
								<input class="full-input" type="text" name="Objet" placeholder="Titre" required><br>

								<textarea name="Bogue" rows="10" cols="140" placeholder="Description" required></textarea><br>

							</div>

							<?php
								if(!isset($_SESSION["username"])){
									echo "<div data-tip='Must be logged in to submit a bug'>
							    				<input type='submit' value='Soumettre' disabled>
											</div>";
								}
								else{
									echo "<input type='submit' value='Soumettre'>";
								}
							 ?>
						</form>
					</div>
				</div>
				<div class="flex horinzontal filterWrapper dark">
					<div class="flex big vertical bugs">
						<h2>Pourquoi signaler une erreur?</h2>
						<p>La participation des utilisateurs pour la découverte et la signalisation des erreurs permet aux développeurs de plus rapidement déceler et corriger les situations non souhaitables qu'il est possible de rencontrer lors de son expérience sur le site ou dans le jeu. N'hésitez surtout pas à nous faire part des erreurs que vous rencontrez.</p>

						<p>Lorsque vous signalez une erreur, les développeurs qui ont participé à la création du jeu recevrons un courriel tiré du formulaire ci-haut afin d'être rapidement avisés de votre rapport.</p>

						<p>Merci et bonne aventure!</p>
					</div>
				</div>
		</div>
	</div>

	<?php require_once("$root/public/layout/footer.php"); ?>
</body>
</html>
