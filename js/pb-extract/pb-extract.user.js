function download(filename, text) {
    var element = document.createElement('a');
    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
    element.setAttribute('download', filename);
    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);
}

function extractListItem(item) {
    var spans = item.getElementsByTagName('span');
    var title, link;
    for (var i = 0; i < spans.length; ++i) {
        var span = spans.item(i);
        var classes = span.classList;
        if (classes.contains('item-name')) {
            title = span.innerText;
        } else if (classes.contains('item-icons')) {
            var links = span.getElementsByTagName('a');
            link = links.item(0).href;
        }
    }
    return [title, link];
}

var list = document.getElementById('torrents');

var items = list.getElementsByTagName('li');

var content = '';

for (var i = 0; i < items.length; ++i) {
    var item = items.item(i);
    var classes = item.classList;
    if (classes.contains('list-entry')) {
        [title, link] = extractListItem(item);
        content += title + ', ' + link + "\n";
    }
}

var fileName = document.location.href
    .match(/\?q=.*/)[0]
    .substr(3)
    .replaceAll(':', '_');

download(fileName + '.txt', content);
