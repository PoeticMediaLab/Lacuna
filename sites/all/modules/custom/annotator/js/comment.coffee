#
# Allow users to view and create threaded replies to annotations
#
# Mike Widner <mikewidner@stanford.edu>
#
class Annotator.Plugin.Comment extends Annotator.Plugin

  commentClasses: {
    "hidden": "annotator-comment-hidden"
    "reply": "annotator-comment fa fa-reply"
  }

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @updateViewer
    })

  # Add a textarea for replies
  addReplyArea: (field, annotation) =>
    form = document.createElement("form")
    form.id = "annotator-comment-form"
    textarea = document.createElement("textarea")
    textarea.classList.add("annotator-comment")
    buttons = document.createElement("div")
    buttons.classList.add("annotator-comment-controls")
    save = document.createElement("a")
    save.classList.add("annotator-comment-save")
    save.innerHTML = "Save"
    save.addEventListener("click", (event) => @saveComment(event, annotation, textarea))
    cancel = document.createElement("a")
    cancel.classList.add("annotator-comment-cancel")
    cancel.innerHTML = "Cancel"
    cancel.addEventListener("click", () => @cancelComment(textarea))
    buttons.appendChild(cancel)
    buttons.appendChild(save)
    form.appendChild(textarea)
    form.appendChild(buttons)
    form.addEventListener("click", (event) => @addComment(event, annotation))
    field.appendChild(form)

  show: (field) =>
    field.classList.remove(@commentClasses.hidden)

  hide: (field) =>
    field.classList.add(@commentClasses.hidden)

  toggleVisibility: (field) =>
    if @commentClasses.hidden in field.classList
      @show(field)
    else
      @hide(field)

  updateViewer: (field, annotation) =>
    n_comments = 0
    replies = "Replies"
    if Object.keys(annotation.comments).length > 0
      n_comments = Object.keys(annotation.comments).length
      if n_comments == 1
        replies = "Reply"
    for className in @commentClasses.reply.split(" ")
      field.classList.add(className)
    span = document.createElement("span")
    if n_comments > 0
      span.innerHTML = "#{n_comments} #{replies}"
      span.addEventListener("click", (event) => @showComments(event, annotation))
      field.appendChild(span)
    else
      span.innerHTML = "Reply"
      span.addEventListener("click", () => @toggleVisibility(replyArea))
      field.appendChild(span)
      replyArea = @addReplyArea(field, annotation)
      @hide(replyArea)

  showComments: (event, annotation) =>
    console.log(annotation.comments)

  saveComment: (event, annotation, textarea) =>
    annotation.new_comment = {}
    annotation.new_comment.pid = 0 # parent id, should be the parent cid or 0
    annotation.new_comment.text = textarea.value
    annotation.new_comment.uid = Drupal.settings.annotator_comment.current_uid # current user ID
    @annotator.updateAnnotatation(annotation)
    @hide(event.target.parentNode)

  cancelComment: (textarea) =>
    textarea.value = ""
    @hide(textarea.parentNode)

  addComment: (event, annotation) =>
    target = event.target.parentNode || event.srcElement.parentNode

