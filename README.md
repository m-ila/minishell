* [readme formatting](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)

# To do

* [ ] parse si commande est valable
* n'est pas valable si ruling quotes pas pair
* est valable si commande est "vide" (geree par exec, penser a bien mod la var de g_ret)
* [ ] creer variable ```$?``` et assign var globale dds, ou plutot si lancee juste afficher g_ret ?
* [ ] put builtins in the main program
* [x] put env in the main program
* [x] deal if env vide with the new env system (char * and not linked list)
* [ ] en fonction des quotes, "charger" var ou non
* [ ] reigning quotes in cmd_struct to epur properly
* [ ] signaux
* [ ] clean header and files
* [ ] put everything to the norm
* [x] why cmd empty causes program to close
* [ ] heredoc ne doit pas update l'history (sujet, parsing donc + Marianne)
* [ ] if cmds is only sep -> if no token after (```coucou | ```) syntax error, if token after (```coucou | > salut```) syntax error on ```>```, if just empty cmd without any redir token, just change glob variable to 2 for unproper use of bash

### Chourael
* [ ] redirections
* Chemin absolu ET relatif (sujet) -> si env -i, cwd va donner quoi ? donc relatif va donner quoi ??
* [ ] heredoc
* heredoc ne doit pas update l'history (sujet, parsing donc + Marianne)

### Marianne
* [x] env
* [ ] make that envp = envi
* [ ] builtins
* [ ] finish parsing quotes
* [x] find where the issue with empty cmd ends up closing
* [x] fix ft_strncmp comp in loop

### Builtins modifications
* [ ] changer la valeur de retour de chaque fonction (doit pouvoir retourner un code erreur en fonction du soucis, par exemple cd et echo peuvent retourner des valeurs d'erreurs différentes)
* [ ] adapter les fonctions aux structs
* [ ] changer printfs et perror en ft_printf_fd
* [ ] pour ft_cd :
* [ ] pour ft_echo : gérer les quotes, les espaces et les variables d'env depuis raw_str
* [x] pour ft_unset : leak lorsqu'on unset le premier elem de l'env, somehow

## Case 1

![note](img_readme/env_variable.png)

## Case 2

![note](img_readme/SHLVL.png)
* When unset SHLVL, SHLVL is set as 0 but still in env

## Case 3
* OLDPWD will only be in the env when cd has been used since the launch of the terminal : needs to be changed once cd is created
* Issue : readline quand chaine vide ferme le prog, alors que le terminal just new prompt