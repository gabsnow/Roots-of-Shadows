<!--news.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: News page of the website for Roots of Shadows: every announcement by the developpers
	will be made here, updates of the game, release dates, etc. -->
<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Nouvelles</title>
	<meta charset="UTF-8">
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
</head>
<body>
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require_once("/$root/public/layout/topmenu.php");
	?>

	<div class="body">
		<div class="filterWrapper full-width min-full-height flex vertical font-white">
			<h1 class="centext">Nouvelles</h1>
			<?php
				if(isset($_SESSION["admin"]) && $_SESSION["admin"] == TRUE) { ?>
					<label class="lbl-button"><div class="button green" onclick="toggleForm(this)"><i class="fas fa-plus-circle"></i><label>Nouvelle publication</label></div></label>

					<div class="hidden-form">
						<form class="form flex vertical font-black" action="index.php?action=submitPost" method="post">
							<input type="field" name="title" placeholder="Titre" required>
							<textarea class="field" name="content" rows="8" cols="80" placeholder="Description" required></textarea>
							<input type="submit" name="SubmitNewPost" value="Envoyer la publication">
						</form>
					</div> <?php
				}

				if(!empty($news)) {
					foreach ($news as $new) { ?>
						<div class="flex horinzontal filterWrapper dark">
							<div class="flex tiny vertical profile-box">
								<label class="lbl-username"><?=$new["username"]?></label>
								<div class="img-box small">
									<img src="/public/images/roots_logo.png">
								</div>
							</div>
							<div class="flex big vertical">
								<label class="lbl-title"><?=$new["title"]?></label>
								<div class="break">
									<?=nl2br($new["description"])?>
								</div>
								<label class="lbl-date"><?=$new["creationDate"] ?></label>
							</div>
						</div> <?php
					}
				}
				else { ?>
					<p style="text-align: center"> Pas de nouvelle.</p> <?php
				}
			?>
		</div>
	</div>

	<?php include_once("/$root/public/layout/footer.php"); ?>


<script type="text/javascript">
	function toggleForm(e) {
		var label = e.querySelector("label");
		var form = document.querySelector(".hidden-form, .shown-form");
		var	i = e.querySelector("i");

		switch (label.innerText) {
			case "Nouvelle publication":
				label.innerText = "Annuler";
				e.style.transition = "0.5s";
				e.classList.remove("green");
				e.classList.add("gray");
				form.classList.remove("hidden-form");
				form.classList.add("shown-form");
				form.style.animation = "SlideDown 1s";
				i.style.transform = "rotate(135deg)";
				i.style.transition = "0.5s";
				break;
			default:
				label.innerText = "Nouvelle publication";
								e.style.transition = "0.5s";
				e.classList.remove("gray");
				e.classList.add("green");
				form.classList.remove("shown-form");
				form.classList.add("hidden-form");
				i.style.transform = "rotate(0deg)";
				i.style.transition = "0.5s";
				break;
		}
	}
</script>

</body>
</html>
