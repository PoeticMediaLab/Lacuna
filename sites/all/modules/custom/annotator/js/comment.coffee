#
# Allow users to view and create threaded replies to annotations
#
# Mike Widner <mikewidner@stanford.edu>
#
class Annotator.Plugin.Comment extends Annotator.Plugin

  commentClass: "annotator-comment fa fa-reply"

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @updateViewer
    })

  updateViewer: (field, annotation) =>
    n_comments = 0
    replies = "Replies"
    if Object.keys(annotation.comments).length > 0
      n_comments = Object.keys(annotation.comments).length
      if n_comments == 1
        replies = "Reply"
    for className in @commentClass.split(" ")
      field.classList.add(className)
    if n_comments > 0
      field.innerHTML = "<span>#{n_comments} #{replies}</span>"
      field.addEventListener("click", (event) => @showComments(event, annotation))
    else
      field.innerHTML = "<span>Reply</span>"
      field.addEventListener("click", (event) => @addComment(event, annotation))

  showComments: (event, annotation) =>
    console.log(annotation.comments)

  saveComment: (event, textarea) =>
    console.log(textarea.value)

  addComment: (event, annotation) =>
    target = event.target.parentNode || event.srcElement.parentNode
    console.log(target)
    target.firstChild.removeEventListener("click", @addComment)  # so multiple textareas don't get created
    form = document.createElement("form")
    form.id = "annotator-comment-form"
    target.appendChild(form)
    textarea = document.createElement("textarea")
    textarea.classList.add("annotator-comment")
    buttons = document.createElement("div")
    buttons.classList.add("annotator-comment-controls")
    save = document.createElement("a")
    save.classList.add("annotator-comment-save")
    save.innerHTML = "Save"
    cancel = document.createElement("a")
    cancel.classList.add("annotator-comment-cancel")
    cancel.innerHTML = "Cancel"
    buttons.appendChild(cancel)
    buttons.appendChild(save)
    form.appendChild(textarea)
    form.appendChild(buttons)
#    textarea.addEventListener("input", (event) => @saveComment(event, textarea))
