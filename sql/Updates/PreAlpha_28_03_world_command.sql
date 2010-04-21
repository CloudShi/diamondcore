DELETE FROM command WHERE name IN('character deleted list', 'character deleted restore', 'character deleted delete');
INSERT INTO command (name, security, help) VALUES
 ('character deleted list', 3, 'Syntax: .character deleted list [$guid|$name]\r\n\r\nShows a list with all deleted characters.\r\nIf $name is supplied, only characters with that string in their name will be selected, if $guid is supplied, only the character with that GUID will be selected.')
,('character deleted restore', 3, 'Syntax: .character deleted restore $guid|$name [$newname]\r\n\r\nRestores deleted characters.\r\nIf $name is supplied, only characters with that string in their name will be restored, if $guid is supplied, only the character with that GUID will be restored.\r\nIf $newname is set, the character will be restored with that name instead of the original one. This works only with one character!')
,('character deleted delete', 3, 'Syntax: .character deleted delete $guid|$name\r\n\r\nCompletely deletes the selected characters.\r\nIf $name is supplied, only characters with that string in their name will be deleted, if $guid is supplied, only the character with that GUID will be deleted.')
;