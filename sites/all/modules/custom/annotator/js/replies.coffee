#
# Allow users to view and create threaded replies to annotations
#
# Mike Widner <mikewidner@stanford.edu>
#
class Annotator.Plugin.Replies extends Annotator.Plugin

  replyClasses: {
    "hidden": "annotator-reply-hidden"
    "reply": "annotator-reply fa fa-reply"
  }

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @updateViewer
    })

  # Add a textarea for replies
  addReplyArea: (field, annotation) =>
    form = document.createElement("form")
    form.id = "annotator-reply-form"
    textarea = document.createElement("textarea")
    textarea.classList.add("annotator-reply")
    buttons = document.createElement("div")
    buttons.classList.add("annotator-reply-controls")
    save = document.createElement("a")
    save.classList.add("annotator-reply-save")
    save.innerHTML = "Save"
    save.addEventListener("click", (event) => @saveComment(event, annotation, textarea))
    cancel = document.createElement("a")
    cancel.classList.add("annotator-reply-cancel")
    cancel.innerHTML = "Cancel"
    cancel.addEventListener("click", () => @cancelComment(textarea))
    buttons.appendChild(cancel)
    buttons.appendChild(save)
    form.appendChild(textarea)
    form.appendChild(buttons)
    form.addEventListener("click", (event) => @addComment(event, annotation))
    field.appendChild(form)

  show: (field) =>
    field.classList.remove(@replyClasses.hidden)

  hide: (field) =>
    field.classList.add(@replyClasses.hidden)

  toggleVisibility: (field) =>
    if @replyClasses.hidden in field.classList
      @show(field)
    else
      @hide(field)

  addReplyLink: (field) =>
    span = document.createElement("span")
    span.innerHTML = "Reply"
    span.addEventListener("click", () => @toggleVisibility(replyArea))
    field.appendChild(span)
    replyArea = @addReplyArea(field, annotation)
    @hide(replyArea)

  updateViewer: (field, annotation) =>
    n_replies = Object.keys(annotation.comments).length
    replies_text = "Replies"
    if n_replies == 1
      replies_text = "Reply"  # because English
    for className in @replyClasses.reply.split(" ")
      field.classList.add(className)
    if n_replies > 0
      span = document.createElement("span")
      span.innerHTML = "#{n_replies} #{replies_text}"
      span.addEventListener("click", (event) => @showReplies(event, annotation))
      field.appendChild(span)
    else
      @addReplyLink(field)

  showReplies: (event, annotation) =>
    console.log(annotation.comments)

  saveReply: (event, annotation, textarea) =>
    annotation.reply = {}
    annotation.reply.pid = 0 # parent id, should be the parent cid or 0
    annotation.reply.text = textarea.value
    annotation.reply.uid = Drupal.settings.annotator_replies.current_uid # current user ID
    @annotator.updateAnnotatation(annotation)
    @hide(event.target.parentNode)

  cancelReply: (textarea) =>
    textarea.value = ""
    @hide(textarea.parentNode)

  addReply: (event, annotation) =>
    target = event.target.parentNode || event.srcElement.parentNode

