.pragma library


function cutPathEnd(path) {
    if (typeof path !== 'string' ||
            path.split('/').length < 2) {
        return ""
    }

    let words = path.split('/')
    return words[words.length - 1]
}

function cutOffPathEnd(path) {
    if (typeof path !== 'string' ||
            path.split('/').length < 2 ||
            path.split('/')[1] === "") {
        return ""
    }

    return path.slice(0, path.lastIndexOf('/') + 1)
}
