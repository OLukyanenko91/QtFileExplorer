.pragma library


function cutPathEnd(path) {
    if (typeof path !== 'string' ||
            path.split('/').length < 2) {
        return ""
    }

    let words = path.split('/')
    return words[words.length - 1]
}
