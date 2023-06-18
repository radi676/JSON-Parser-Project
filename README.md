# JSON Parser
Course project for "Object-oriented programming with C++" @ Faculty of Mathematics and Informatics, Sofia Univeristy

### Commands

- `open <file path> `- load a file in the json parser
- `close` - close opened file
- `save [<json path>]` - save opened file, or a part of it
- `saveas <path> [<json path>]` - save opened file(or a part of it) as new file
- `exit` - close the editor
- `create <json path> <json element>` - create json element in the path specified
- `delete <json path>` - delete json element by path specified
- `move <json path from> <json path to>` - move json element from a path to another
- `set <json path> <json element>` - set a value of specific path to some element
- `search <key>` - search in the whole document for a key
- `help` - print help message


### Remarks about usage

#### Arguments
- Any argument containing space(' ') should be bounded by double quotes(`"<argument>"`)
- If the argument contains any quotes characters("), it should be escaped(\") and the argument has to be surrounded with quotes(")

#### Path
- Json path is a sequence of keys delimitered by period(.)
- Every valid Json path starts from the root object($)
- Valid key can be written as plain text or surronded by the following: `[' <key> ']`
- Any array index is written as `[ <array index> ]` with no separating dot needed beforehand.
- Example for valid Json path: `$.firstLevel.['second'].array[1].['another space'][2].last`

#### Regex
- Search supports simple regex matching as follows: asterisk(*) matching 0,1 or multiple symbols, question mark(?) mathing exactly one symbol.
- Any regex needed to match the symbol asterisk(*) or question mark(?) must escape it
- Example for valid regex: `start*end?in\*` matches words starting in `start` and ending in `end_in*`


### Resources
`MyString` implementation - [Angel Dimitriev](<https://github.com/Angeld55/Object-oriented_programming_FMI>)
`Optional` implementation - [Angel Dimitriev](<https://github.com/Angeld55/Object-oriented_programming_FMI>)
`Pair` implementation -  [Angel Dimitriev](<https://github.com/Angeld55/Object-oriented_programming_FMI>)
`SharedPtr` implementation - [Angel Dimitriev](<https://github.com/Angeld55/Object-oriented_programming_FMI>)