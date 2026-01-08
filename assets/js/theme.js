const themes = ["github-light", "github-dark", "tokyonight", "gruvbox"];

function setTheme(theme) {
  document.documentElement.setAttribute("data-theme", theme);
  localStorage.setItem("theme", theme);
}

function toggleTheme() {
  const current = localStorage.getItem("theme") || "github-light";
  let index = themes.indexOf(current);
  index = (index + 1) % themes.length;
  setTheme(themes[index]);
}

// Load saved theme
const saved = localStorage.getItem("theme");
if (saved) {
  setTheme(saved);
  current = themes.indexOf(saved);
}
