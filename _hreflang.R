# Post-render script: links each English page with its Spanish translation
# (and vice versa) using <link rel="alternate" hreflang="..."> tags, so search
# engines treat them as translations instead of duplicates. It also adds the
# Spanish sitemap to the English robots.txt, since crawlers only read
# the robots.txt at the root of the domain.
#
# Used by both _quarto.yml and es/_quarto.yaml. Quarto does not support
# hreflang natively.

site_url <- c(en = "https://book-hpc.ggvy.cl/", es = "https://book-hpc.ggvy.cl/es/")

project_dir <- normalizePath(Sys.getenv("QUARTO_PROJECT_DIR", "."))
output_dir  <- Sys.getenv("QUARTO_PROJECT_OUTPUT_DIR", "_book")
if (!grepl("^/", output_dir))
  output_dir <- file.path(project_dir, output_dir)

lang    <- if (basename(project_dir) == "es") "es" else "en"
en_root <- if (lang == "es") dirname(project_dir) else project_dir

# Only the pages that exist in both languages
pages <- list.files(output_dir, pattern = "\\.html$")
pages <- pages[
  file.exists(file.path(en_root, sub("html$", "qmd", pages))) &
  file.exists(file.path(en_root, "es", sub("html$", "qmd", pages)))
  ]

for (page in pages) {

  fn   <- file.path(output_dir, page)
  html <- readLines(fn, warn = FALSE, encoding = "UTF-8")

  if (any(grepl("hreflang=\"x-default\"", html, fixed = TRUE)))
    next

  head_end <- which(grepl("</head>", html, fixed = TRUE))[1]
  if (is.na(head_end))
    next

  path <- if (page == "index.html") "" else page
  tags <- sprintf(
    '<link rel="alternate" hreflang="%s" href="%s%s">',
    c("en", "es", "x-default"),
    site_url[c("en", "es", "en")],
    path
  )

  html <- append(html, tags, after = head_end - 1)
  writeLines(html, fn, useBytes = TRUE)

}

robots <- file.path(output_dir, "robots.txt")
if (lang == "en" && file.exists(robots)) {
  txt <- readLines(robots, warn = FALSE)
  es_sitemap <- paste0("Sitemap: ", site_url["es"], "sitemap.xml")
  if (!es_sitemap %in% txt)
    writeLines(c(txt, es_sitemap), robots)
}

message(sprintf("hreflang: annotated %i pages (%s)", length(pages), lang))
