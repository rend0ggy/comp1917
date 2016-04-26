<?php
$blogs = array("doomsday","http","chessboard","mandelbrot");
?>
<!doctype html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Jack Renshaw's COMP1917 Blog</title>
<link rel="stylesheet" href="styles.css" type="text/css" />
<meta name="viewport" content="width=device-width, minimum-scale=1.0, maximum-scale=1.0" />
</head>

<body>

		<section id="body" class="width">
			<aside id="sidebar" class="column-left">

			<header>
				<h1><a href="#">rend0g</a></h1>

				<h2>Where i blog about my adventures in COMP1917</h2>
				
			</header>

			<nav id="mainnav">
  				<ul>
                            		<li
                            		<?php
                            		if(!isset($_GET["blog"])){
                            			echo ' class="selected-item"';
                            		}
                            		?>
                            		><a href="https://rend0g.com/comp1917/blog">Home</a></li>
                            	<?php
                            		foreach($blogs as $value){
                            			echo "<li";
                            		if($_GET["blog"] == $value){
                            			echo ' class="selected-item"';
                            		}
                            			echo "><a href='?blog={$value}'>$value</a></li>";
                            		}
                            		?>
                        	</ul>
			</nav>

			
			
			</aside>
			<section id="content" class="column-right">
<?php
if(isset($_GET["blog"])){
	if(in_array($_GET["blog"],$blogs))
	{
		$text = file_get_contents("blogFiles/{$_GET["blog"]}");
		$text = str_replace("\n", "<br>", $text);
	echo "<article>";
	echo "<h2>{$_GET["blog"]} -  a blog by Jack Renshaw</h2>";
	echo "<p>{$text}</p>";
	echo "<a href='#' class='button button-reversed'>Share</a>";
	echo "</article>";
		}else{
?>
	    <article>
				
			
			<h2>Sorry, this blog doesn't exist!</h2>
			<div class="article-info">Posted on <time datetime="2016-04-05">05 April</time> by <a href="#" rel="author">Jack Renshaw</a></div>

            <p>You may have misentered the link</p>

<p>Entries are stored in individual text files in this directory. Entries include only the raw text of the blog. PHP parses special characters for formatting (newline, etc). The GET value in the URL doesn't correspond to any file in the directory</p>	

<p>You can see all available entries in the menu on the left hand side of the page</p>

		<a href="#" class="button">Read more</a>
		<a href="#" class="button button-reversed">Share</a>


		
		</article>
<?php
}
}else{
?>
	    <article>
				
			
			<h2>Welcome to my blog</h2>
			<div class="article-info">Posted on <time datetime="2016-04-05">05 April</time> by <a href="#" rel="author">Jack Renshaw</a></div>

            <p>Welcome to my blog. This is where i post about my trials and tribulations with the COMP1917 course. I have created my own website primarily because i hate the interface of openlearning (i can't even scroll down to see activities!) and also to develop my technical skills beyond the scope of the course</p>

<p>Entries are stored in individual text files in this directory. Entries include only text based data. PHP parses the text file and looks for special formatting indicators which it converts to html entities</p>	

<p>You can see all available entries in the menu on the left hand side of the page</p>

		<a href="#" class="button">Read more</a>
		<a href="#" class="button button-reversed">Share</a>


		
		</article>
<?php
foreach($blogs as $value)
{
	$text = substr(file_get_contents("blogFiles/{$value}"),0,150);
	echo "<article>";
	echo "<h2>{$value}</h2>";
	echo "<p>{$text}...</p>";
	echo "<a href='?blog={$value}' class='button'>Read more</a> ";
	echo "<a href='#' class='button button-reversed'>Share</a>";
	echo "</article>";
}


?>
<?php
}
?>
		</article>

			
			<footer class="clear">
				<p>&copy; 2016 rend0g.com</p>
			</footer>

		</section>

		<div class="clear"></div>

	</section>
	

</body>
</html>